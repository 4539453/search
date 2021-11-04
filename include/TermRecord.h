#ifndef TERM_RECORD_H
#define TERM_RECORD_H

#include <vector>
#include <set>

class TermRecord {
private:
  unsigned int DocID;
  std::vector<unsigned int> TermPositions;

public:
  TermRecord(unsigned int DocID);
  TermRecord(unsigned int DocID, std::vector<unsigned int> &TermPositions);
  unsigned int docID() const;
  const std::vector<unsigned int> &termPositions() const;
  virtual bool operator<(const TermRecord &Tr);
  void addTermPosition(unsigned int Position);
  void addTermPositions(std::vector<unsigned int> &Positions);
  void addTermPositionsSet(std::set<unsigned int> &Positions);
};

#endif
