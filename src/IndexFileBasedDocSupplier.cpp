#include "IndexFileBasedDocSupplier.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>

IndexFileBasedDocSupplier::IndexFileBasedDocSupplier(std::string DocFilesRoot,
                                                     std::string IndexFileName)
    : IndexFileName{IndexFileName}, DocFilesRoot{DocFilesRoot},
      CurrentDocSeq{0}, DocumentList{new std::vector<Document>()} {
  std::ifstream IndexFile(DocFilesRoot + IndexFileName);
  std::string LineInIndexFile;
  std::vector<std::string> FileDetailContainer;
  while (getline(IndexFile, LineInIndexFile)) {
    boost::split(FileDetailContainer, LineInIndexFile, boost::is_any_of(","));
    int DocId;
    std::stringstream Did(FileDetailContainer[0]);
    Did >> DocId;
    std::string Title = FileDetailContainer[2];
    if (FileDetailContainer.size() > 4) {
      for (auto i = 3; i <= FileDetailContainer.size() - 2; i++) {
        Title = Title + "," + FileDetailContainer[i];
      }
    }
    Document Doc(DocId, DocFilesRoot + FileDetailContainer[1], Title,
                 FileDetailContainer.back());
    DocumentList->push_back(Doc);
  }
}

Document *IndexFileBasedDocSupplier::get() {
  if (CurrentDocSeq == DocumentList->size()) {
    return nullptr;
  }
  return &((*DocumentList)[CurrentDocSeq++]);
}

std::vector<Document> *IndexFileBasedDocSupplier::documentList() {
  return this->DocumentList;
}

IndexFileBasedDocSupplier::~IndexFileBasedDocSupplier() { delete DocumentList; }
