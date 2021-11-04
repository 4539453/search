#ifndef TERM_ID_MAPPING_H
#define TERM_ID_MAPPING_H

#include <string>
#include <unordered_map>

class TermIDMapping {
private:
  std::unordered_map<std::string, unsigned int> TermIDMap;

public:
  TermIDMapping();
  unsigned int getTermIdOf(std::string Word);
  void loadMappingFromFile(std::string FilePath);
  ~TermIDMapping();
};

#endif
