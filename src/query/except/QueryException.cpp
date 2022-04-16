#include "query/except/QueryException.h"

QueryException::QueryException(const char *Msg) : ErrorMessage{Msg} {}

const char *QueryException::what() const noexcept { return ErrorMessage; }
