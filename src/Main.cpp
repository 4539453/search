#include <iostream>

#include "InvertedIndex.h"
#include "query/Interpreter.h"
#include "query/Lexer.h"
#include "query/Parser.h"
#include "query/ast/ResultComputingNodeVisitor.h"
#include "IndexFileBasedDocSupplier.h"
#include "util/SimpleTokenizer.h"

int main() {
  std::string DocFilesRoot = "../resources/txts/";
  std::string IndexFileName = "index.txt";
  std::string MappingFilePath = DocFilesRoot + IndexFileName;

  TermIDMapping TermIDMap;
  TermIDMap.loadMappingFromFile(MappingFilePath);

  IndexFileBasedDocSupplier IFBDocSupplier(DocFilesRoot, IndexFileName);
  SimpleTokenizer Tokenizer;
  InvertedIndex IIndex;
  IIndex.build(IFBDocSupplier, Tokenizer, TermIDMap);
  ResultComputingNodeVisitor RCNVisitor(IIndex, TermIDMap);
  std::string Query;
  std::cout << "Enter query string (ctrl-d to exit) : ";
  while (getline(std::cin, Query)) {
    Lexer Lexer(Query);
    Parser Parser(Lexer);
    Interpreter Interpreter(Parser, RCNVisitor);
    auto Result = Interpreter.computeSearchResult();
    // TODO add details and pretty print result
    for (auto TRecord : Result) {
      std::cout << TRecord.docID() << '\n';
    }
    std::cout << "Enter query string (ctrl-d to exit) : ";
  }
  return 0;
}
