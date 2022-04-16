#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "query/ast/WordASTNode.h"
#include <set>

class Interpreter {
private:
  Parser Parser;
  ResultComputingNodeVisitor ResultComputingNodeVisitor;
  // NodeVisitor PrintVisitor;
public:
  Interpreter(Parser Parser);
  Interpreter(Parser, ResultComputingNodeVisitor);
  set<TermRecord, TermRecordCompare> computeSearchResult();
};

#endif
