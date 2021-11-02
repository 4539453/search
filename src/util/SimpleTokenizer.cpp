#include "util/SimpleTokenizer.h"
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <vector>

std::vector<std::string> *SimpleTokenizer::tokenize(std::string Text) {
  std::vector<std::string> *Words = new std::vector<std::string>();
  std::function<void(std::string)> addToWordsIfNotEmpty =
      [Words](std::string Word) {
        if (!Word.empty()) {
          std::transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
          Words->push_back(Word);
        }
      };
  char C;
  std::string Word;
  for (auto I = 0; I < Text.length(); ++I) {
    C = Text.at(I);
    if (C == ' ' || C == '\t' || C == '\n') {
      addToWordsIfNotEmpty(Word);
      Word.clear();
    } else {
      Word += C;
    }
  }
  addToWordsIfNotEmpty(Word);
  return Words;
}
