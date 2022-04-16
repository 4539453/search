#ifndef TOKEN_H
#define TOKEN_H

#include "query/TokenType.h"
#include <string>

class Token {
private:
  TokenType Type;
  std::string Value;

public:
  Token(TokenType Type, std::string Value);
  Token(char C);
  TokenType type();
  std::string value();
};
#endif
