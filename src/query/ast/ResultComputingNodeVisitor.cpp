#include "query/ast/ResultComputingNodeVisitor.h"
#include "query/Token.h"
#include "query/except/QueryException.h"
#include <algorithm>
#include <iostream>

ResultComputingNodeVisitor::ResultComputingNodeVisitor(InvertedIndex &IIndex,
                                                       TermIDMapping &Map)
    : Index{IIndex}, TermIDMap{Map} {}

void ResultComputingNodeVisitor::visit(BinaryOpASTNode *Node) {
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

void ResultComputingNodeVisitor::visit(WordASTNode *Node) {
  Node->result().clear();
  std::string Word = Node->word();
  std::transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
  unsigned int TermID = 0;
  try {
    TermID = this->TermIDMap.getTermIdOf(Word);
  } catch (std::out_of_range &Except) {
    std::cout << "New Word\n";
  }

  auto TermRecords = this->Index.getRecordsOfTermWithID(TermID);
  Node->result().insert(TermRecords.begin(), TermRecords.end());
  Node->isEvaluated();
}
