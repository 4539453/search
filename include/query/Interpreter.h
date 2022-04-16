#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "query/ast/WordASTNode.h"
#include <set>

class Interpreter : NodeVisitor {
public:
  void visit(BinaryOpASTNode *Node) override;
  void visit(WordASTNode *Node) override;
  virtual std::set<TermRecord, TermRecordCompare>
  compute(BinaryOpASTNode *Node) = 0;
  virtual std::set<TermRecord, TermRecordCompare>
  compute(WordASTNode *Node) = 0;
};

#endif
