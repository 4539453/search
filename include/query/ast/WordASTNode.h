#ifndef WORD_AST_NODE_H
#define WORD_AST_NODE_H

#include "query/Token.h"
#include "query/ast/ASTNode.h"
#include "query/ast/NodeVisitor.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include <string>

class WordASTNode : public ASTNode {
private:
  Token WordToken;

public:
  WordASTNode(Token WordToken);
  std::string word();
  void accept(NodeVisitor &Visitor) override;
  std::set<TermRecord, TermRecordCompare>
  acceptComputingVisitor(ResultComputingNodeVisitor &Visitor) override;
  ~WordASTNode();
};
#endif
