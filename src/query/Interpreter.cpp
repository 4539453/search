#include "query/Interpreter.h"

Interpreter::Interpreter(Parser Parser) : Parser{Parser} {}

Interpreter::Interpreter(Parser Parser,
                         ResultComputingNodeVisitor ResultComputingNodeVisitor)
    : Parser{Parser}, ResultComputingNodeVisitor{ResultComputingNodeVisitor} {}

set<TermRecord, TermRecordCompare> Interpreter::computeSearchResult() {
  ASTNode *Node = this->Parser.parse();
  Node->accept(this->ResultComputingNodeVisitor);
  auto ResultSet(Node->evaluatedResult()); // uses move constructor
  delete Node;
  return ResultSet;
}
