#ifndef NODE_PRINT_VISITOR_H
#define NODE_PRINT_VISITOR_H

#include "query/ast/NodeVisitor.h"
#include "query/ast/WordASTNode.h"
#include "query/ast/BinaryOpASTNode.h"

class NodePrintVisitor : NodeVisitor {
  public:
    void visit(BinaryOpASTNode *Node) override;
    void visit(WordASTNode *Node) override;
};
#endif
