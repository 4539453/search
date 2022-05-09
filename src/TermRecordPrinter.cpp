#include "TermRecordPrinter.h"
#include "IndexFileBasedDocSupplier.h"
#include <iostream>

TermRecordPrinter::TermRecordPrinter(std::string FilesRoot,
                                     std::string IndexFileName)
    : DocIDMap{} {
  IndexFileBasedDocSupplier IFBDocSupplier(FilesRoot, IndexFileName);
  for (auto Doc : *(IFBDocSupplier.documentList())) {
    this->DocIDMap.emplace(Doc.getID(), Doc);
  }
}

void TermRecordPrinter::print(TermRecord &TR) {
  auto Doc = this->DocIDMap.at(TR.docID());
  auto DocFilePath = Doc.getFilePath();
  std::cout << "Title : " << Doc.getTitle() << '\n';
  std::cout << "Author : " << Doc.getAuthor() << '\n';
  this->showTextAroundTwoOccurences(Doc, TR);
}

void TermRecordPrinter::printAll(
    std::set<TermRecord, TermRecordCompare> &TRSet) {
  for (auto TR : TRSet) {
    this->print(TR);
    std::cout << "\n\n";
  }
}

void TermRecordPrinter::showTextAroundTwoOccurences(Document &Doc,
                                                    TermRecord &TR) {
  auto TermPositions = TR.termPositions();
  auto PosIt = TermPositions.begin();
  auto FirstOcc = *PosIt;
  auto SecondOcc = -1;
  ++PosIt;
  if (PosIt != TermPositions.end()) {
    SecondOcc = *PosIt;
  }
  // TODO show text from the doc highlighting query words
}
