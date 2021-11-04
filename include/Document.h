#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>

class Document {
protected:
  int Id;
  std::string FilePath;
  std::string Title;
  std::string Author;

public:
  Document(int Id, std::string FilePath, std::string Title, std::string Author);
  int getID();
  std::string getFilePath();
  std::string getTitle();
  std::string getAuthor();
};

#endif
