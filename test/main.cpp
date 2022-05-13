#include <iostream>
#include <locale>
#include "../OleanderStemmingLibrary/include/olestem/stemming/english_stem.h"


std::string stemWord(std::string &rawWord) {
  std::wstring wstr(rawWord.begin(), rawWord.end());
  static stemming::english_stem<> enStem;
  enStem(wstr);
  rawWord = std::string(wstr.begin(), wstr.end());
  return rawWord;
}

int main() {
  // std::setlocale(LC_ALL, "Russian_Russia.1251");
  std::setlocale(LC_ALL, "en_US.UTF-8");

  // std::wcout.imbue(std::locale("Russian_Russia.1251"));



  std::string Query;
  std::cout << "Enter query string (^D to exit) : ";
  while (getline(std::cin, Query)) {

    // std::cout << std::string(Query.begin(), Query.end()) << '\n';
    std::cout << Query << '\n';
    std::cout << stemWord(Query) << '\n';

    // std::cout << (std::string(Query.begin(), Query.end()) == std::string("fd")) << '\n';

    std::cout << "Enter query string (^D to exit) : ";

  }
  std::cout << '\n';
  return 0;
}


