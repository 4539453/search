#include "query/Interpreter.h"
#include "query/except/QueryException.h"

void Interpreter::visit(BinaryOpASTNode *Node) {
  Node->isEvaluated();
  Node->result().clear();
  Node->left()->accept(*this);
  Node->right()->accept(*this);
  auto LeftResult = Node->left()->evaluatedResult();
  auto RightResult = Node->right()->evaluatedResult();
  switch (Node->op().type()) {
  case TokenType::AND:
    std::set_intersection(LeftResult.begin(), LeftResult.end(),
                          RightResult.begin(), RightResult.end(),
                          std::inserter(Node->result(), Node->result().end()));
    break;
  case TokenType::OR:
    std::set_union(LeftResult.begin(), LeftResult.end(), RightResult.begin(),
                   RightResult.end(),
                   std::inserter(Node->result(), Node->result().end()));
    break;
  case TokenType::NOT:
    std::set_difference(LeftResult.begin(), LeftResult.end(),
                        RightResult.begin(), RightResult.end(),
                        std::inserter(Node->result(), Node->result().end()));
    break;
  default:
    throw QueryException("Invalid operation");
  }
}
void Interpreter::visit(WordASTNode *Node) {
  Node->isEvaluated();
  Node->result().clear();
  // Node->result()({}); //TODO Inverted-Index query
}
std::set<TermRecord, TermRecordCompare>
Interpreter::compute(BinaryOpASTNode *Node) {
  return {};
}
std::set<TermRecord, TermRecordCompare>
Interpreter::compute(WordASTNode *Node) {
  return {};
}
