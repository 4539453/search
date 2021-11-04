#include "Document.h"
#include <string>

Document::Document(int Id, std::string FilePath, std::string Title,
                   std::string Author)
    : Id{Id}, FilePath{FilePath}, Title{Title}, Author{Author} {}
int Document::getID() { return Id; }
std::string Document::getFilePath() { return FilePath; }
std::string Document::getTitle() { return Title; }
std::string Document::getAuthor() { return Author; }
