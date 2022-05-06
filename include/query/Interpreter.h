#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "query/Parser.h"
#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/NodePrintVisitor.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "query/ast/WordASTNode.h"
#include <set>

class Interpreter {
private:
  Parser QueryParser;
  ResultComputingNodeVisitor RCNodeVisitor;
  NodePrintVisitor PrintVisitor;

public:
  Interpreter(Parser, ResultComputingNodeVisitor);
  std::set<TermRecord, TermRecordCompare> computeSearchResult();
};

#endif
