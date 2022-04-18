#include "query/ast/ResultComputingNodeVisitor.h"

ResultComputingNodeVisitor::ResultComputingNodeVisitor(InvertedIndex &IIndex,
                                                       TermIDMapping &Map)
    : Index{IIndex}, TermIDMap{Map} {}

ResultComputingNodeVisitor::visit(BinaryOpASTNode *Node) {
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
  Node->isEvaluated();
}

ResultComputingNodeVisitor::visit(WordASTNode *Node) {
  Node->result().clear();
  auto TermRecords = this->Index.getRecordsOfTermWithID(
      this->TermIDMap.getTermIdOf(Node->word()));
  Node->result().insert(TermRecords.begin(), TermRecords.end());
  Node->isEvaluated();
}
