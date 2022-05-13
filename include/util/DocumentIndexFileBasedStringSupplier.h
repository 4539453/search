#ifndef UTIL_DIFILEBASEDSTRINGSUPPLIER_H
#define UTIL_DIFILEBASEDSTRINGSUPPLIER_H

#include "Document.h"
#include "util/StringSupplier.h"
#include <string>
#include <vector>

class DocumentIndexFileBasedStringSupplier : public StringSupplier {
private:
  std::string IndexFileName;
  std::string TextFilesRoot;
  std::vector<Document> *DocumentList;
  std::string TextToSupply;

public:
  DocumentIndexFileBasedStringSupplier(std::string TextFilesRoot,
                                       std::string IndexFileName);
  bool hasMore() override;
  std::string get() override;
  ~DocumentIndexFileBasedStringSupplier();
};

#endif
