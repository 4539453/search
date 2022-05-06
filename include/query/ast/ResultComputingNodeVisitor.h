#ifndef RESULT_COMPUTING_NODE_VISITOR_H
#define RESULT_COMPUTING_NODE_VISITOR_H

#include "InvertedIndex.h"
#include "compare/TermRecordCompare.h"
#include "query/ast/ASTNode.h"
#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/WordASTNode.h"
#include <set>

class ResultComputingNodeVisitor : public NodeVisitor {
private:
  InvertedIndex &Index;
  TermIDMapping &TermIDMap;

public:
  ResultComputingNodeVisitor(InvertedIndex &, TermIDMapping &);
  void visit(BinaryOpASTNode *Node) override;
  void visit(WordASTNode *Node) override;
};
#endif
