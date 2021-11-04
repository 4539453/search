#include "InvertedIndex.h"
#include "DocumentSupplier.h"
#include "TermIDMapping.h"
#include "util/Tokenizer.h"

#include <algorithm>
#include <functional>
#include <set>
#include <string>
#include <iostream>
#include <fstream>

InvertedIndex::InvertedIndex() {}

InvertedIndex::~InvertedIndex() {}

void InvertedIndex::build(DocumentSupplier &DocumentSupplier,
                          Tokenizer &Tokenizer, TermIDMapping &TermIDMapping) {
  std::function<std::string(Document)> getTextOfDocument =
      [](Document Document) -> std::string {
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
  auto PostingsListIter = std::find_if(
      PostingsListSet.begin(), PostingsListSet.end(),
      [&](const PostingsList &ThisPostingsList) -> bool {
        return ThisPostingsList.termID() == OtherPostingsList.termID();
      });
  if (PostingsListIter != PostingsListSet.end()) {
    PostingsList CombinedPostingsList(PostingsListIter->termID(), PostingsListIter->termRecords());
    PostingsListSet.erase(*PostingsListIter);
    for (auto &TermRecordOut : OtherPostingsList.termRecords()) {
      CombinedPostingsList.add(TermRecordOut);
    }
    
    PostingsListSet.insert(CombinedPostingsList);
    return;
  }
  PostingsListSet.insert(OtherPostingsList);
}

const std::set<TermRecord, TermRecordCompare> &
InvertedIndex::getRecordsOfTermWithID(unsigned int TermID) const {
  std::set<PostingsList>::iterator PostingsListIter =
      std::find_if(PostingsListSet.begin(), PostingsListSet.end(),
                   [&](const PostingsList &ThisPostingsList) -> bool {
                     return ThisPostingsList.termID() == TermID;
                   });
  if (PostingsListIter != PostingsListSet.end()) {
    return PostingsListIter->termRecords();
  }
  return {};
}
