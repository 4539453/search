#ifndef POSTINGS_LIST_COMPARE_H
#define POSTINGS_LIST_COMPARE_H

#include "PostingsList.h"

class PostingsListCompare {
public:
  bool operator()(const PostingsList &LPostingsList,
                  const PostingsList &RPostingsList) const;
};
#endif
