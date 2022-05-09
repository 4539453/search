#ifndef TERM_RECORD_PRINTER_H
#define TERM_RECORD_PRINTER_H

#include "Document.h"
#include "TermRecord.h"
#include "compare/TermRecordCompare.h"
#include <map>
#include <set>
#include <string>

class TermRecordPrinter {
private:
  std::map<unsigned int, Document> DocIDMap;
  void showTextAroundTwoOccurences(Document &, TermRecord &);

public:
  TermRecordPrinter(std::string IndexFilePath, std::string IndexFileName);
  void print(TermRecord &TermR);
  void printAll(std::set<TermRecord, TermRecordCompare> &TermRecordSet);
};

#endif
