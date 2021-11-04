#include "gtest/gtest.h"
#include <set>
#include <string>

#include "IndexFileBasedDocSupplier.h"
#include "InvertedIndex.h"
#include "TermIDMapping.h"
#include "TermRecord.h"
#include "util/SimpleTokenizer.h"

TEST(InvertedIndexTest, Test1) {
  std::string IndexFileName = "index.txt";
  std::string TxtFilesRoot = "test/resources/txts/";
  IndexFileBasedDocSupplier IndexFileBasedDocSupplier("test/resources/txts/",
                                                      "index.txt");
  SimpleTokenizer SimpleTokenizer;
  TermIDMapping TermIDMapping;
  TermIDMapping.loadMappingFromFile(TxtFilesRoot + "TermIDMapping.txt");

  InvertedIndex InvertedIndex;
  InvertedIndex.build(IndexFileBasedDocSupplier, SimpleTokenizer,
                      TermIDMapping);
  std::set<TermRecord, TermRecordCompare> TermRecordSetOfDoc3{
      InvertedIndex.getRecordsOfTermWithID(TermIDMapping.getTermIdOf("doc3"))};
  EXPECT_EQ(1, TermRecordSetOfDoc3.size());
  std::set<TermRecord, TermRecordCompare> TermRecordSetOfSome{
      InvertedIndex.getRecordsOfTermWithID(TermIDMapping.getTermIdOf("some"))};
  EXPECT_EQ(3, TermRecordSetOfSome.size());
}
