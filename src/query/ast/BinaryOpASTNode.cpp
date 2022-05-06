#include "query/ast/BinaryOpASTNode.h"

BinaryOpASTNode::BinaryOpASTNode(ASTNode *Left, Token Op, ASTNode *Right)
    : Left{Left}, Op{Op}, Right{Right} {}

ASTNode *BinaryOpASTNode::left() { return Left; }
ASTNode *BinaryOpASTNode::right() { return Right; }
Token BinaryOpASTNode::op() { return Op; }

void BinaryOpASTNode::accept(NodeVisitor &Visitor) { Visitor.visit(this); }

BinaryOpASTNode::~BinaryOpASTNode() {
  delete Left;
  delete Right;
}
