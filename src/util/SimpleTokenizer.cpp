#include "util/SimpleTokenizer.h"

#include <algorithm>
#include <functional>

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

std::map<std::string, std::set<unsigned int>>
SimpleTokenizer::tokenize2(std::string Text) {
  std::map<std::string, std::set<unsigned int>> MapOfTermsAndPositions;
  std::function<void(std::string, unsigned int)> addToMapIfWordNotEmpty =
      [&MapOfTermsAndPositions =
           MapOfTermsAndPositions](std::string Word, unsigned int Position) {
        if (!Word.empty()) {
          std::transform(Word.begin(), Word.end(), Word.begin(), ::tolower);
          auto It = MapOfTermsAndPositions.find(Word);
          if (It == MapOfTermsAndPositions.end()) {
            MapOfTermsAndPositions.insert({Word, {}});
          }
          MapOfTermsAndPositions.at(Word).insert(Position);
        }
      };
  char C;
  std::string Word;
  for (auto I = 0; I < Text.length(); ++I) {
    C = Text.at(I);
    if (C == ' ' || C == '\t' || C == '\n') {
      addToMapIfWordNotEmpty(Word, I - Word.size());
      Word.clear();
    } else {
      Word += C;
    }
  }
  addToMapIfWordNotEmpty(Word, Text.length() - Word.size());
  return MapOfTermsAndPositions;
}
