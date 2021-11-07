#ifndef POSTINGS_LIST_H
#define POSTINGS_LIST_H

#include "TermRecord.h"
#include "compare/TermRecordCompare.h"
#include <set>

class PostingsList {
private:
  unsigned int TermID;
  std::set<TermRecord, TermRecordCompare> TermRecords;

public:
  PostingsList();
  PostingsList(unsigned int TermID);
  PostingsList(unsigned int TermID,
               std::set<TermRecord, TermRecordCompare> TermRecords);
  unsigned int termID() const;
  const std::set<TermRecord, TermRecordCompare> &termRecords() const;
  void add(const TermRecord &TermRecord);
};

#endif
