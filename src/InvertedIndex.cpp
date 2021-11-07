#include "InvertedIndex.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>

InvertedIndex::InvertedIndex() {}

InvertedIndex::~InvertedIndex() {}

void InvertedIndex::build(DocumentSupplier &DocumentSupplier,
                          Tokenizer &Tokenizer, TermIDMapping &TermIDMapping) {
  std::cout << "Building Inverted Index...\n";

  std::function<std::string(Document)> getTextOfDocument =
      [](Document Document) -> std::string {
    //        std::cout << "Getting text of document \""<<Document.getTitle() <<
    //        "\"\n";
    std::string DocText = "";
    std::string FilePath = Document.getFilePath();
    std::ifstream Ifs(FilePath, std::ios::in | std::ios::binary);
    Ifs.seekg(0, std::ios::end);
    DocText.resize(Ifs.tellg());
    Ifs.seekg(0, std::ios::beg);
    Ifs.read(DocText.data(), DocText.size());
    Ifs.close();
    return DocText;
  };
  while (auto Doc = DocumentSupplier.get()) {
    for (auto TermPosPair : Tokenizer.tokenize2(getTextOfDocument(*Doc))) {
      auto Term = TermPosPair.first;
      auto TermPosSet = TermPosPair.second;
      TermRecord TermRecord(Doc->getID());
      TermRecord.addTermPositionsSet(TermPosSet);
      PostingsList PostingsList(TermIDMapping.getTermIdOf(Term));
      PostingsList.add(TermRecord);
      addPostingsList(PostingsList);
    }
  }
}

void InvertedIndex::addPostingsList(PostingsList &OtherPostingsList) {
  // std::cout << "Adding PostingsList of term with id " <<
  // OtherPostingsList.termID() << "\n";
  auto PostingsListIter = PostingsListSet.find(OtherPostingsList);
  if (PostingsListIter != PostingsListSet.end()) {
    //  std::cout << "Merging with existing PostingsList...\n";
    PostingsList CombinedPostingsList(PostingsListIter->termID(),
                                      PostingsListIter->termRecords());
    PostingsListSet.erase(*PostingsListIter);
    for (auto &TermRecordOut : OtherPostingsList.termRecords()) {
      CombinedPostingsList.add(TermRecordOut);
    }

    PostingsListSet.insert(CombinedPostingsList);
    return;
  }
  // std::cout << "Inserting into PostingsListSet...\n";
  PostingsListSet.insert(OtherPostingsList);
}

const std::set<TermRecord, TermRecordCompare> &
InvertedIndex::getRecordsOfTermWithID(unsigned int TermID) const {
  PostingsList DummyPostingsList(TermID);
  std::set<PostingsList>::iterator PostingsListIter =
      PostingsListSet.find(DummyPostingsList);
  if (PostingsListIter != PostingsListSet.end()) {
    return PostingsListIter->termRecords();
  }
  // std::cout << "No term records found for term with id " << TermID << '\n';
  return {};
}
