#include "util/TermIDMapper.h"
#include "util/StringSupplier.h"
#include "gtest/gtest.h"
#include <random>
#include <string>
#include <unordered_map>

class MapReturningTermIDMapper : public TermIDMapper {
public:
  MapReturningTermIDMapper(class StringSupplier &StringSupplier)
      : TermIDMapper{StringSupplier} {}
  const std::unordered_map<std::string, unsigned int> &getTermIDMapping() {
    return TermIDMap;
  }
};

class SampleStringSupplier : public StringSupplier {
private:
  int IterCount;
  std::string Words[11];

public:
  SampleStringSupplier()
      : IterCount{0}, Words{"a1",  "a2",  "a3", "b1", "BC1",    "CD2",
                            "CD2", "DES", "EF", "FG", "N.e.R.C"} {}
  bool hasMore() {
    if (IterCount < 11) {
      ++IterCount;
      return true;
    }
    return false;
  }
  std::string get() {
    std::string Text{""};
    for (auto i = 0; i < IterCount; ++i) {
      Text += " " + Words[i];
    }
    return Text;
  }
};

TEST(TermIDMapperTest, Test1) {
  SampleStringSupplier SStringSupplier;
  MapReturningTermIDMapper TermIDMapper(SStringSupplier);
  TermIDMapper.createMap();
  std::unordered_map<std::string, unsigned int> Mapping =
      TermIDMapper.getTermIDMapping();
  EXPECT_EQ(1, Mapping.at("a1"));
  EXPECT_EQ(2, Mapping.at("a2"));
  EXPECT_EQ(6, Mapping.at("cd2"));
  EXPECT_EQ(10, Mapping.at("n.e.r.c"));
}
