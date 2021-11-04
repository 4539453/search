#ifndef TERM_RECORD_COMPARE_H
#define TERM_RECORD_COMPARE_H

#include "TermRecord.h"

class TermRecordCompare {
public:
  bool operator() (const TermRecord &LTermRecord, const TermRecord &RTermRecord) const;
};
#endif
