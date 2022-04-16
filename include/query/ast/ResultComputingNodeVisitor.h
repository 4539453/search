#ifndef RESULT_COMPUTING_NODE_VISITOR_H
#define RESULT_COMPUTING_NODE_VISITOR_H

#include "compare/TermRecordCompare.h"
#include "query/ast/ASTNode.h"
#include <set>

class BinaryOpASTNode;
class WordASTNode;

class ResultComputingNodeVisitor {
public:
  virtual std::set<TermRecord, TermRecordCompare>
  compute(BinaryOpASTNode *Node) = 0;
  virtual std::set<TermRecord, TermRecordCompare>
  compute(WordASTNode *Node) = 0;
};
#endif
