#ifndef UTIL_STRING_SUPPLIER_H
#define UTIL_STRING_SUPPLIER_H

#include <memory>
#include <string>

class StringSupplier {
public:
  virtual bool hasMore() = 0;
  virtual std::string get() = 0;
};

#endif
