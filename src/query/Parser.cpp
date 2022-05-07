#include "query/Parser.h"
#include "query/ast/BinaryOpASTNode.h"
#include "query/ast/WordASTNode.h"
#include "query/except/QueryException.h"

Parser::Parser(class Lexer &Lexer)
    : Lexer{Lexer}, CurrentToken{Lexer.getNextToken()} {}

ASTNode *Parser::parse() { return this->expr(); }

void Parser::verifyTokenAndAdvance(TokenType Type) {
  if (this->CurrentToken.type() == Type) {
    this->CurrentToken = this->Lexer.getNextToken();
  } else {
    throw QueryException("Invalid Syntax");
  }
}

/*
 *  grammar
 *
 *  expr  : uset (NOT uset)*
 *  uset  : nset (OR nset)*
 *  nset  : set (AND set)*
 *  set   : WORD | LPAREN expr RPAREN
 *
 *  nset('∩'set) - result of intersections
 *  uset('∪'set) - result of union
 */
ASTNode *Parser::expr() {
  ASTNode *Node{this->uset()};
  while (this->CurrentToken.type() == TokenType::NOT) {
    Token T(this->CurrentToken.type(), this->CurrentToken.value());
    this->verifyTokenAndAdvance(TokenType::NOT);
    Node = new BinaryOpASTNode(Node, T, this->uset());
  }
  return Node;
}

// uset  : nset (OR nset)*
ASTNode *Parser::uset() {
  ASTNode *Node{this->nset()};
  while (this->CurrentToken.type() == TokenType::OR) {
    Token T(this->CurrentToken.type(), this->CurrentToken.value());
    this->verifyTokenAndAdvance(TokenType::OR);
    Node = new BinaryOpASTNode(Node, T, this->nset());
  }
  return Node;
}

//  nset  : set (AND set)*
ASTNode *Parser::nset() {
  ASTNode *Node{this->set()};
  while (this->CurrentToken.type() == TokenType::AND) {
    Token T(this->CurrentToken.type(), this->CurrentToken.value());
    this->verifyTokenAndAdvance(TokenType::AND);
    Node = new BinaryOpASTNode(Node, T, this->set());
  }
  return Node;
}

//  set   : WORD | LPAREN expr RPAREN
ASTNode *Parser::set() {
  Token T(this->CurrentToken.type(), this->CurrentToken.value());
  if (T.type() == TokenType::WORD) {
    this->verifyTokenAndAdvance(TokenType::WORD);
    return new WordASTNode(T);
  }
  if (T.type() == TokenType::LPAREN) {
    this->verifyTokenAndAdvance(TokenType::LPAREN);
    ASTNode *Node{this->expr()};
    this->verifyTokenAndAdvance(TokenType::RPAREN);
    return Node;
  }
  throw QueryException("Invalid Syntax");
}
