#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "query/TokenType.h"

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
