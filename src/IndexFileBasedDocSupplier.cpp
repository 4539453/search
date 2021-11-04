#include "IndexFileBasedDocSupplier.h"
#include "Document.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

IndexFileBasedDocSupplier::IndexFileBasedDocSupplier(std::string DocFilesRoot,
                                                     std::string IndexFileName)
    : IndexFileName{IndexFileName}, DocFilesRoot{DocFilesRoot},
      CurrentDocSeq{0}, DocumentList{new std::vector<Document>()} {
  std::ifstream IndexFile(DocFilesRoot + IndexFileName);
  std::string LineInIndexFile;
  std::vector<std::string> FileDetailContainer;
  while (IndexFile >> LineInIndexFile) {
    boost::split(FileDetailContainer, LineInIndexFile, boost::is_any_of(","));
    int DocId;
    std::stringstream Did(FileDetailContainer[0]);
    Did >> DocId;
    Document Doc(DocId, DocFilesRoot + FileDetailContainer[1],
                 FileDetailContainer[2], FileDetailContainer[3]);
    DocumentList->push_back(Doc);
  }
}

Document *IndexFileBasedDocSupplier::get() {
  if (CurrentDocSeq == DocumentList->size()) {
    return nullptr;
  }
  return &((*DocumentList)[CurrentDocSeq++]);
}

IndexFileBasedDocSupplier::~IndexFileBasedDocSupplier() { delete DocumentList; }
