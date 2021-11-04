#include "TermRecord.h"

TermRecord::TermRecord(unsigned int DocID) : DocID{DocID} {}

TermRecord::TermRecord(unsigned int DocID,
                       std::vector<unsigned int> &TermPositions)
    : DocID{DocID}, TermPositions(TermPositions) {}

unsigned int TermRecord::docID() const { return DocID; }

const std::vector<unsigned int> &TermRecord::termPositions() const {
  return TermPositions;
}

bool TermRecord::operator<(const TermRecord &Tr) { return DocID < Tr.docID(); }

void TermRecord::addTermPosition(unsigned int Position) {
  TermPositions.insert(TermPositions.begin(), Position);
}

void TermRecord::addTermPositions(std::vector<unsigned int> &Positions) {
  TermPositions.insert(TermPositions.begin(), Positions.begin(),
                       Positions.end());
}

void TermRecord::addTermPositionsSet(std::set<unsigned int> &Positions) {
  TermPositions.insert(TermPositions.begin(), Positions.begin(),
                       Positions.end());
}
