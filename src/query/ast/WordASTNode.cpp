#include "query/ast/WordASTNode.h"

WordASTNode::WordASTNode(Token WordToken) : WordToken{WordToken} {}

std::string WordASTNode::word() { return WordToken.value(); }

WordASTNode::~WordASTNode() {}
