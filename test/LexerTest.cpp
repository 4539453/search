#include "query/Lexer.h"
#include "gtest/gtest.h"
#include <string>

TEST(LexerTest, Test1) {
  std::string Query = "abc def";
  Lexer Lex(Query);
  EXPECT_EQ("abc", Lex.getNextToken().value());
  EXPECT_EQ("&", Lex.getNextToken().value());
  EXPECT_EQ("def", Lex.getNextToken().value());
}

TEST(LexerTest, Test2) {
  std::string Query = "abc56~67def";
  Lexer Lex(Query);
  EXPECT_EQ("abc56", Lex.getNextToken().value());
  EXPECT_EQ("~", Lex.getNextToken().value());
  EXPECT_EQ("67def", Lex.getNextToken().value());
}

TEST(LexerTest, Test3) {
  std::string Query = "(abc def)~abcdef";
  Lexer Lex(Query);
  EXPECT_EQ("(", Lex.getNextToken().value());
  EXPECT_EQ("abc", Lex.getNextToken().value());
  EXPECT_EQ("&", Lex.getNextToken().value());
  EXPECT_EQ("def", Lex.getNextToken().value());
  EXPECT_EQ(")", Lex.getNextToken().value());
  EXPECT_EQ("~", Lex.getNextToken().value());
  EXPECT_EQ("abcdef", Lex.getNextToken().value());
}
