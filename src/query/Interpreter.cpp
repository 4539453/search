#include "query/Interpreter.h"
#include <iostream>

Interpreter::Interpreter(Parser Parser,
                         ResultComputingNodeVisitor ResultComputingNodeVisitor)
    : QueryParser{Parser}, RCNodeVisitor{ResultComputingNodeVisitor},
      PrintVisitor{} {}

std::set<TermRecord, TermRecordCompare> Interpreter::computeSearchResult() {
  ASTNode *Node = this->QueryParser.parse();
  std::cout << "Query as a Scheme expression: ";
  Node->accept(this->PrintVisitor);
  std::cout << '\n';
  Node->accept(this->RCNodeVisitor);
  auto ResultSet(Node->evaluatedResult()); // uses move constructor
  delete Node;
  return ResultSet;
}
