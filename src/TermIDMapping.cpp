#include "TermIDMapping.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <fstream>
#include <string>

TermIDMapping::TermIDMapping() : TermIDMap() {}

void TermIDMapping::loadMappingFromFile(std::string FilePath) {
  std::ifstream FileStream(FilePath);
  boost::archive::text_iarchive iarch(FileStream);
  iarch >> TermIDMap;
}

unsigned int TermIDMapping::getTermIdOf(std::string Word) {
  return TermIDMap.at(Word);
}

TermIDMapping::~TermIDMapping() {}
