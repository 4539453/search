#include "query/Parser.h"
#include "query/Lexer.h"
#include "query/ast/NodePrintVisitor.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>

TEST(ParserTest, Test1) {
  std::string Query = "abc3    def efg";
  Lexer Lex(Query);
  Parser QParser(Lex);
  NodePrintVisitor PrintVisitor;
  QParser.parse()->accept(PrintVisitor);
  std::cout << '\n';
}

TEST(ParserTest, Test2) {
  std::string Query = "34abc~def";
  Lexer Lex(Query);
  Parser QParser(Lex);
  NodePrintVisitor PrintVisitor;
  QParser.parse()->accept(PrintVisitor);
  std::cout << '\n';
}

TEST(ParserTest, Test3) {
  std::string Query = "(osman | asaf) & billion";
  Lexer Lex(Query);
  Parser QParser(Lex);
  NodePrintVisitor PrintVisitor;
  QParser.parse()->accept(PrintVisitor);
  std::cout << '\n';
}
