#include "util/DocumentIndexFileBasedStringSupplier.h"
#include "util/TermIDMapper.h"
#include "gtest/gtest.h"
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

TEST(DIFSupplierTest, Test1) {
  DocumentIndexFileBasedStringSupplier SSupplier("test/resources/txts/",
                                                 "index.txt");
  MapReturningTermIDMapper TermIDMapper(SSupplier);
  TermIDMapper.createMap();
  std::unordered_map<std::string, unsigned int> Mapping =
      TermIDMapper.getTermIDMapping();
  EXPECT_EQ(7, Mapping.at("doc1"));
  EXPECT_EQ(2, Mapping.at("text"));
  EXPECT_EQ(4, Mapping.at("test"));
  EXPECT_EQ(6, Mapping.at("doc2"));
  EXPECT_EQ(1, Mapping.at("doc3"));
}
