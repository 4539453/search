#ifndef UTIL_SIMPLETOKENIZER_H
#define UTIL_SIMPLETOKENIZER_H

#include "util/Tokenizer.h"
#include <map>
#include <string>
#include <vector>

class SimpleTokenizer : public Tokenizer {
private:
  std::string stemWord(std::string &rawWord);
public:
  std::vector<std::string> *tokenize(const std::string &Text) override;
  std::map<std::string, std::set<unsigned int>>
  tokenize2(const std::string &Text) override;
};

#endif
