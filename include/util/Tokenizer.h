#ifndef UTIL_TOKENIZER_H
#define UTIL_TOKENIZER_H

#include <memory>
#include <string>
#include <vector>

class Tokenizer {
public:
  virtual std::vector<std::string> *tokenize(std::string Text) = 0;
};

#endif
