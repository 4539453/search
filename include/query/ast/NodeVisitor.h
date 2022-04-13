#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include "query/ast/ASTNode.h"

class BinaryOpASTNode;
class WordASTNode;

class NodeVisitor {
  public:
    virtual void visit(BinaryOpASTNode *Node) = 0;
    virtual void visit(WordASTNode *Node) = 0;
};
#endif
