#include "TermRecordPrinter.h"
#include <iostream>
#include "IndexFileBasedDocSupplier.h" 

TermRecordPrinter::TermRecordPrinter(std::string FilesRoot, std::string IndexFileName):DocIDMap{} {
  IndexFileBasedDocSupplier IFBDocSupplier(FilesRoot, IndexFileName);
 for(auto Doc : *(IFBDocSupplier.documentList())) {
  this->DocIDMap.emplace(Doc.getID(), Doc);
 }
}

void TermRecordPrinter::print(TermRecord &TR) {
  auto Doc = this->DocIDMap.at(TR.docID());
  auto DocFilePath = Doc.getFilePath();
  std::cout << "Title : " << Doc.getTitle() << '\n'; 
  std::cout << "Author : " << Doc.getAuthor() << '\n'; 
  //TODO show text from the doc highlighting query wordss
}

void TermRecordPrinter::printAll(std::set<TermRecord, TermRecordCompare>  &TRSet) {
  for(auto TR : TRSet) {
    this->print(TR);
    std::cout << "\n\n";
  }
}

