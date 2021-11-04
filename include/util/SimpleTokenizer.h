#ifndef UTIL_SIMPLETOKENIZER_H
#define UTIL_SIMPLETOKENIZER_H

#include "util/Tokenizer.h"
#include <map>
#include <string>
#include <vector>

class SimpleTokenizer : public Tokenizer {
public:
  std::vector<std::string> *tokenize(std::string Text) override;
  std::map<std::string, std::set<unsigned int>>
  tokenize2(std::string Text) override;
};

#endif
