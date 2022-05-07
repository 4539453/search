#include "query/ast/NodePrintVisitor.h"
#include <iostream>

void NodePrintVisitor::visit(BinaryOpASTNode *Node) {
  std::cout << "(" << Node->op().value() << " ";
  Node->left()->accept(*this);
  std::cout << " ";
  Node->right()->accept(*this);
  std::cout << ")";
}

void NodePrintVisitor::visit(WordASTNode *Node) { std::cout << Node->word(); }
