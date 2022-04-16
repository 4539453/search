#ifndef RESULT_COMPUTING_NODE_VISITOR_H
#define RESULT_COMPUTING_NODE_VISITOR_H

#include "compare/TermRecordCompare.h"
#include "query/ast/ASTNode.h"
#include <set>

class BinaryOpASTNode;
class WordASTNode;

class ResultComputingNodeVisitor : NodeVisitor {
public:
  void visit(BinaryOpASTNode *Node) override;
  void visit(WordASTNode *Node) override;
};
#endif
