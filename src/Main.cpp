#include <iostream>

#include "IndexFileBasedDocSupplier.h"
#include "InvertedIndex.h"
#include "query/Interpreter.h"
#include "query/Lexer.h"
#include "query/Parser.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "util/SimpleTokenizer.h"

int main() {
  std::string DocFilesRoot = "../test/resources/txts/";
  std::string IndexFileName = "index.txt";
  std::string MappingFileName = "TermIDMapping.txt";
  std::string MappingFilePath = DocFilesRoot + MappingFileName;

  TermIDMapping TermIDMap;
  TermIDMap.loadMappingFromFile(MappingFilePath);

  IndexFileBasedDocSupplier IFBDocSupplier(DocFilesRoot, IndexFileName);
  SimpleTokenizer Tokenizer;
  InvertedIndex IIndex;
  IIndex.build(IFBDocSupplier, Tokenizer, TermIDMap);
  ResultComputingNodeVisitor RCNVisitor(IIndex, TermIDMap);
  std::string Query;
  std::cout << "Enter query string (Ctrl+D to exit) : ";
  while (getline(std::cin, Query)) {
    Lexer Lexer(Query);
    Parser Parser(Lexer);
    Interpreter Interpreter(Parser, RCNVisitor);
    auto Result = Interpreter.computeSearchResult();
    // TODO add details and pretty print result
    std::cout << Result.size() << " result";
    if (Result.size() == 1) {
      std::cout << ".\n";
    } else {
      std::cout << "s.\n";
    }
    for (auto TRecord : Result) {
      std::cout << TRecord.docID() << '\n';
    }
    std::cout << "Enter query string (Ctrl+D to exit) : ";
  }
  std::cout << '\n';
  return 0;
}
