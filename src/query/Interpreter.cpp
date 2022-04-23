#include "query/Interpreter.h"

Interpreter::Interpreter(Parser Parser,
                         ResultComputingNodeVisitor ResultComputingNodeVisitor)
    : QueryParser{Parser}, RCNodeVisitor{ResultComputingNodeVisitor} {}

std::set<TermRecord, TermRecordCompare> Interpreter::computeSearchResult() {
  ASTNode *Node = this->QueryParser.parse();
  Node->accept(this->RCNodeVisitor);
  auto ResultSet(Node->evaluatedResult()); // uses move constructor
  delete Node;
  return ResultSet;
}
