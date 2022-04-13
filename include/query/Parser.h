#ifndef PARSER_H
#define PARSER_H

#include "query/Lexer.h"
#include "query/ast/ASTNode.h"

class Parser {
  private:
    Lexer Lexer;
    Token CurrentToken;
    void verifyTokenAndAdvance(TokenType Type);
    ASTNode *expr();
    ASTNode *uset();
    ASTNode *nset();
    ASTNode *set();
  public:
    Parser(class Lexer Lexer);
    ASTNode *parse();
};

#endif
