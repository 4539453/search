#ifndef DOCUMENT_SUPPLIER_H
#define DOCUMENT_SUPPLIER_H

#include "Document.h"

class DocumentSupplier {
public:
  virtual Document *get() = 0;
};

#endif
