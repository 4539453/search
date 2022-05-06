#include "query/ast/ASTNode.h"
#include "query/except/QueryException.h"

ASTNode::ASTNode() : IsEvaluated{false}, Result() {}

void ASTNode::isEvaluated() { this->IsEvaluated = true; }

bool ASTNode::evaluated() { return this->IsEvaluated; }

std::set<TermRecord, TermRecordCompare> &ASTNode::result() { return Result; }

std::set<TermRecord, TermRecordCompare> ASTNode::evaluatedResult() {
  if (this->IsEvaluated) {
    return Result;
  }
  throw QueryException("Tried to access result before evaluating");
}

ASTNode::~ASTNode() {}
