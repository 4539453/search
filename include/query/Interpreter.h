#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "query/ast/WordASTNode.h"
#include <set>
#include "query/Parser.h"

class Interpreter {
private:
  Parser QueryParser;
  ResultComputingNodeVisitor RCNodeVisitor;
  // NodeVisitor PrintVisitor;
public:
  Interpreter(Parser, ResultComputingNodeVisitor);
  std::set<TermRecord, TermRecordCompare> computeSearchResult();
};

#endif
