#ifndef RESULT_COMPUTING_NODE_VISITOR_H
#define RESULT_COMPUTING_NODE_VISITOR_H

#include "compare/TermRecordCompare.h"
#include <set>
#include "query/ast/ASTNode.h"

class BinaryOpASTNode;
class WordASTNode;

class ResultComputingNodeVisitor {
  public:
    virtual std::set<TermRecord, TermRecordCompare> compute(BinaryOpASTNode *Node) = 0;
    virtual std::set<TermRecord, TermRecordCompare> compute(WordASTNode *Node) = 0;
};
#endif
