#include "IntSequence.h"

IntSequence::IntSequence() : Current{0} {}

IntSequence::IntSequence(int StartFrom) : Current{StartFrom} {}

IntSequence::next() { return ++Current; }
