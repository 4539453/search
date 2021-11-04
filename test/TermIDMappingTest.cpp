#include "TermIDMapping.h"
#include "util/DocumentIndexFileBasedStringSupplier.h"
#include "util/TermIDMapper.h"
#include "gtest/gtest.h"
#include <string>

TEST(TermIDMappingTest, Test1) {
  DocumentIndexFileBasedStringSupplier SSupplier("test/resources/txts/",
                                                 "index.txt");
  TermIDMapper TermIDMapper(SSupplier);
  TermIDMapper.createMap();
  std::string MappingFile = "test/resources/txts/TermIDMapping.txt";
  TermIDMapper.serializeMapTo(MappingFile);
  TermIDMapping TermIDMapping;
  TermIDMapping.loadMappingFromFile(MappingFile);
  EXPECT_EQ(1, TermIDMapping.getTermIdOf("doc3"));
  EXPECT_EQ(7, TermIDMapping.getTermIdOf("doc1"));
}
