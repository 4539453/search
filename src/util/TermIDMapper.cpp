#include "util/TermIDMapper.h"
#include "util/SimpleTokenizer.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/unordered_map.hpp>
#include <fstream>
#include <vector>

TermIDMapper::TermIDMapper(class StringSupplier &StringSupplier)
    : StringSupplier{StringSupplier}, TermIDMap{}, CurrentID{0} {}

void TermIDMapper::createMap() {
  SimpleTokenizer Tokenizer{};
  while (StringSupplier.hasMore()) {
    for (auto Word : *Tokenizer.tokenize(StringSupplier.get())) {
      if (TermIDMap.find(Word) == TermIDMap.end()) {
        TermIDMap.insert({{Word, ++CurrentID}});
      }
    }
  }
}

void TermIDMapper::serializeMapTo(std::string FilePath) {
  std::ofstream File(FilePath);
  boost::archive::text_oarchive oarch(File);
  oarch << TermIDMap;
}

TermIDMapper::~TermIDMapper() {}
