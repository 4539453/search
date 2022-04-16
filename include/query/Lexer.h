#ifndef LEXER_H
#define LEXER_H

#include <locale>
#include <string>

#include "query/Token.h"

class Lexer {
private:
  std::string Text;
  unsigned int Pos;
  char CurrentChar;
  std::locale Locale;
  std::string TokensOnlyText;
  std::string word();
  void error();
  void advance();
  void skipWhitespace();
  bool isSpecialChar(const char C);
  bool isPrevSpecial();
  bool isCurrentSpecial();

public:
  Lexer(std::string Text);
  Token getNextToken();
};

#endif
