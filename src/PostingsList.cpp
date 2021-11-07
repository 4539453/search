#include "PostingsList.h"

PostingsList::PostingsList() {}

PostingsList::PostingsList(unsigned int TermID) : TermID{TermID} {}

PostingsList::PostingsList(unsigned int TermID,
                           std::set<TermRecord, TermRecordCompare> TermRecords)
    : TermID{TermID}, TermRecords(TermRecords) {}

unsigned int PostingsList::termID() const { return TermID; }

const std::set<TermRecord, TermRecordCompare> &
PostingsList::termRecords() const {
  return TermRecords;
}

void PostingsList::add(const TermRecord &TermRecord) {
  //  std::cout << "Adding TermRecord of term " << TermID << " from doc " <<
  //  TermRecord.docID() << " \n";
  auto TermRecordIter = TermRecords.find(TermRecord);
  if (TermRecordIter == TermRecords.end()) {
    //   std::cout << "No existing term record. Inserting...\n";
    TermRecords.insert(TermRecord);
    return;
  }
  // std::cout << "Merging with existing term record\n";
  std::vector<unsigned int> TermPositionsOfBoth(
      TermRecordIter->termPositions());
  TermPositionsOfBoth.insert(TermPositionsOfBoth.end(),
                             TermRecord.termPositions().begin(),
                             TermRecord.termPositions().end());
  TermRecords.erase(TermRecordIter);
  TermRecords.emplace(TermRecord.docID(), TermPositionsOfBoth);
}
