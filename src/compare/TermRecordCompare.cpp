#include "compare/TermRecordCompare.h"

bool TermRecordCompare::operator() (const TermRecord &LTermRecord,
    const TermRecord &RTermRecord) const {
  return LTermRecord.docID() < RTermRecord.docID();
}
