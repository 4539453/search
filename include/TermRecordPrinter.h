#ifndef TERM_RECORD_PRINTER_H
#define TERM_RECORD_PRINTER_H

#include <map>
#include <string>
#include "TermRecord.h"
#include "Document.h"
#include "compare/TermRecordCompare.h"
#include <set>

class TermRecordPrinter {
  private:
    std::map<unsigned int, Document> DocIDMap;
  public:
    TermRecordPrinter(std::string IndexFilePath, std::string IndexFileName);
    void print(TermRecord &TermR);
    void printAll(std::set<TermRecord, TermRecordCompare> &TermRecordSet);
};

#endif
