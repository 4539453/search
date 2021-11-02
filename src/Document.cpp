#include "Document.h"
#include <string>

Document::Document(int Id, std::string FileName, std::string Title,
                   std::string Author)
    : Id{Id}, FileName{FileName}, Title{Title}, Author{Author} {}
int Document::getID() { return Id; }
std::string Document::getFileName() { return FileName; }
std::string Document::getTitle() { return Title; }
std::string Document::getAuthor() { return Author; }
