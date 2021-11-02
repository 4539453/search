#ifndef UTIL_TERMIDMAPPER_H
#define UTIL_TERMIDMAPPER_H

#include "util/StringSupplier.h"
#include <string>
#include <unordered_map>

class TermIDMapper {
private:
  class StringSupplier &StringSupplier;
  unsigned int CurrentID;

protected:
  std::unordered_map<std::string, unsigned int> TermIDMap;

public:
  TermIDMapper(class StringSupplier &StringSupplier);
  ~TermIDMapper();
  void createMap();
  void serializeMapTo(std::string FilePath);
};

#endif
