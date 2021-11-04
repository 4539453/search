#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "DocumentSupplier.h"
#include "PostingsList.h"
#include "TermIDMapping.h"
#include "compare/PostingsListCompare.h"
#include "util/Tokenizer.h"
#include <set>

class InvertedIndex {
private:
  std::set<PostingsList, PostingsListCompare> PostingsListSet;

public:
  InvertedIndex();
  void build(DocumentSupplier &DocumentSupplier, Tokenizer &Tokenizer,
             TermIDMapping &TermIDMapping);
  void addPostingsList(PostingsList &PostingsList);
  const std::set<TermRecord, TermRecordCompare> &
  getRecordsOfTermWithID(unsigned int TermID) const;
  ~InvertedIndex();
};

#endif
