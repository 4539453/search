#include "query/Lexer.h"
#include "query/except/QueryException.h"
#include <algorithm>
#include <array>

Lexer::Lexer(const std::string &Text) : Text{Text}, Locale("C") {
  Pos = 0;
  CurrentChar = Text[Pos];
}

Token Lexer::getNextToken() {

  if (CurrentChar == '\0') {
    return Token(TokenType::EOL, "");
  }

  if (std::isspace(CurrentChar, Locale)) {
    skipWhitespace();
    if (!isCurrentSpecial() && !isPrevSpecial()) {
      TokensOnlyText.append(1, '&');
      return Token(TokenType::AND, "&");
    }
  }

  if (isCurrentSpecial()) {
    char C = CurrentChar;
    TokensOnlyText.append(1, C);
    advance();
    return Token(C);
  }

  if (std::isalpha(CurrentChar, Locale)) {
    std::string WordTok = word();
    TokensOnlyText.append(WordTok);
    return Token(TokenType::WORD, WordTok);
  }
  throw QueryException("Invalid Character");
}

void Lexer::skipWhitespace() {
  while (CurrentChar != '\0' && std::isspace(CurrentChar, Locale)) {
    advance();
  }
}

void Lexer::advance() {
  Pos += 1;
  if (Pos == Text.size()) {
    CurrentChar = '\0';
  } else {
    CurrentChar = Text[Pos];
  }
}

bool Lexer::isSpecialChar(char C) {
  std::array<char, 5> SpecialChars = {{'(', ')', '&', '|', '~'}};
  return std::any_of(SpecialChars.begin(), SpecialChars.end(),
                     [C](char ArrC) { return C == ArrC; });
}

bool Lexer::isCurrentSpecial() { return isSpecialChar(CurrentChar); }

bool Lexer::isPrevSpecial() { return isSpecialChar(TokensOnlyText.back()); }

std::string Lexer::word() {
  std::string Result;
  while (CurrentChar != '\0' && std::isalpha(CurrentChar, Locale)) {
    Result.append(1, CurrentChar);
    advance();
  }
  return Result;
}
