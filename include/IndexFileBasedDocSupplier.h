#ifndef INDEX_FILE_BASED_DOC_SUPPLIER_H
#define INDEX_FILE_BASED_DOC_SUPPLIER_H

#include "Document.h"
#include "DocumentSupplier.h"
#include <string>
#include <vector>

class IndexFileBasedDocSupplier : public DocumentSupplier {
private:
  std::string IndexFileName;
  std::string DocFilesRoot;
  unsigned int CurrentDocSeq;
  std::vector<Document> *DocumentList;

public:
  IndexFileBasedDocSupplier(std::string DocFilesRoot,
                            std::string IndexFileName);
  std::string getRootDir();
  Document *get() override;
  ~IndexFileBasedDocSupplier();
};

#endif
