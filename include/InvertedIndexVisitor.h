#ifndef INVERTED_INDEX_VISITOR_H
#define INVERTED_INDEX_VISITOR_H

#include "InvertedIndex.h"

class InvertedIndexVisitor {
public:
  virtual void visit(InvertedIndex &InvertedIndex) = 0;
};

#endif
