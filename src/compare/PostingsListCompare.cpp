#include "compare/PostingsListCompare.h"

bool PostingsListCompare::operator()(const PostingsList &LPostingsList,
                                     const PostingsList &RPostingsList) const {
  return LPostingsList.termID() < RPostingsList.termID();
}
