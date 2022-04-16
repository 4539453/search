#include "query/Token.h"

Token::Token(TokenType Type, std::string Value) : Type{Type}, Value{Value} {}

Token::Token(char C) : Token(static_cast<TokenType>(C), std::string(1, C)) {}

TokenType Token::type() { return Type; }

std::string Token::value() { return Value; }
