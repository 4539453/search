#include "util/DocumentIndexFileBasedStringSupplier.h"
#include "Document.h"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

DocumentIndexFileBasedStringSupplier::DocumentIndexFileBasedStringSupplier(
    std::string TextFilesRoot, std::string IndexFileName)
    : TextFilesRoot{TextFilesRoot}, IndexFileName{IndexFileName},
      DocumentList{new std::vector<Document>()} {
  std::ifstream IndexFile(TextFilesRoot + IndexFileName);
  std::string LineInIndexFile;
  std::vector<std::string> FileDetailContainer;
  while (IndexFile >> LineInIndexFile) {
    boost::split(FileDetailContainer, LineInIndexFile, boost::is_any_of(","));
    int DocId;
    std::stringstream Did(FileDetailContainer[0]);
    Did >> DocId;
    Document Doc(DocId, FileDetailContainer[1], FileDetailContainer[2],
                 FileDetailContainer[3]);
    DocumentList->push_back(Doc);
  }
}

bool DocumentIndexFileBasedStringSupplier::hasMore() {
  return !(DocumentList->empty() && TextToSupply.empty());
}

std::string DocumentIndexFileBasedStringSupplier::get() {
  std::function<void(Document)> loadTextOfDocument =
      [&TextFilesRoot = TextFilesRoot,
       &TextToSupply = TextToSupply](Document Document) {
        std::string FilePath = TextFilesRoot + Document.getFilePath();
        std::ifstream Ifs(FilePath, std::ios::in | std::ios::binary);
        Ifs.seekg(0, std::ios::end);
        TextToSupply.resize(Ifs.tellg());
        Ifs.seekg(0, std::ios::beg);
        Ifs.read(TextToSupply.data(), TextToSupply.size());
        Ifs.close();
      };
  if (hasMore()) {
    loadTextOfDocument(DocumentList->back());
    std::string CopyToTextToSupply{TextToSupply};
    TextToSupply = "";
    DocumentList->pop_back();
    return CopyToTextToSupply;
  }
  return "";
}

DocumentIndexFileBasedStringSupplier::~DocumentIndexFileBasedStringSupplier() {
  delete DocumentList;
}
