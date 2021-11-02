#include "util/SimpleTokenizer.h"
#include "gtest/gtest.h"
#include <memory>
#include <string>
#include <vector>

TEST(TokenizerTest, SimpleString1) {
  Tokenizer *Tokenizer = new SimpleTokenizer();
  std::vector<std::string> *tokens = Tokenizer->tokenize("abc");
  EXPECT_EQ(1, tokens->size());
  EXPECT_EQ("abc", tokens->at(0));
  delete tokens;
}

TEST(TokenizerTest, SimpleString2) {
  Tokenizer *Tokenizer = new SimpleTokenizer();
  std::vector<std::string> *tokens = Tokenizer->tokenize("abc  CVfg");
  EXPECT_EQ(2, tokens->size());
  EXPECT_EQ("abc", tokens->at(0));
  EXPECT_EQ("cvfg", tokens->at(1));
  delete tokens;
}

TEST(TokenizerTest, SimpleString3) {
  Tokenizer *Tokenizer = new SimpleTokenizer();
  std::vector<std::string> *tokens = Tokenizer->tokenize("abc  CVfg");
  EXPECT_EQ(2, tokens->size());
  EXPECT_EQ("abc", tokens->at(0));
  EXPECT_EQ("cvfg", tokens->at(1));
  delete tokens;
}

TEST(TokenizerTest, SimpleString4) {
  Tokenizer *Tokenizer = new SimpleTokenizer();
  std::vector<std::string> *tokens = Tokenizer->tokenize("abc  CVfg a.v. B  ");
  EXPECT_EQ(4, tokens->size());
  EXPECT_EQ("abc", tokens->at(0));
  EXPECT_EQ("cvfg", tokens->at(1));
  EXPECT_EQ("a.v.", tokens->at(2));
  EXPECT_EQ("b", tokens->at(3));
  delete tokens;
}
