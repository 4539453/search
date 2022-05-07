LIBFLAGS=-lboost_serialization
GTESTFLAGS=-lgtest -lpthread
SRCROOT=../src
INCLUDEROOT=../include
CC=clang++
CFLAGS=-c -Wall -std=c++17 -I $(INCLUDEROOT)
COMPILE=$(CC) $(CFLAGS) -o $@

install : search
#	mv search ../

search : main.o astnode.o wordnode.o binaryopnode.o rcnvisitor.o \
	interpreter.o parser.o lexer.o queryexcept.o token.o printvisitor.o \
	simpletokenizer.o postingslist.o termrecord.o document.o \
	ifbdocsupplier.o termidmapping.o trcompare.o plcompare.o \
	invertedindex.o trprinter.o
	$(CC) $(LIBFLAGS) -o $@ $^ 

main.o :
	$(COMPILE) $(SRCROOT)/Main.cpp

rcnvisitor.o:
	$(COMPILE) $(SRCROOT)/query/ast/ResultComputingNodeVisitor.cpp 

printvisitor.o:
	$(COMPILE) $(SRCROOT)/query/ast/NodePrintVisitor.cpp 

trprinter.o:
	$(COMPILE) $(SRCROOT)/TermRecordPrinter.cpp

token.o :
	$(COMPILE) $(SRCROOT)/query/Token.cpp

astnode.o:
	$(COMPILE) $(SRCROOT)/query/ast/ASTNode.cpp 

wordnode.o:
	$(COMPILE) $(SRCROOT)/query/ast/WordASTNode.cpp 

binaryopnode.o:
	$(COMPILE) $(SRCROOT)/query/ast/BinaryOpASTNode.cpp

interpreter.o : 
	$(COMPILE) $(SRCROOT)/query/Interpreter.cpp

parser.o :
	$(COMPILE) $(SRCROOT)/query/Parser.cpp

parsertest.o :
	$(COMPILE) ../test/ParserTest.cpp

lexer.o :
	$(COMPILE) $(SRCROOT)/query/Lexer.cpp

lexertest.o :
	$(COMPILE) ../test/LexerTest.cpp

queryexcept.o :
	$(COMPILE) $(SRCROOT)/query/except/QueryException.cpp

gtest.o : 
	$(COMPILE) ../test/gtest_main.cc

invertedindex.o :
	$(COMPILE) $(SRCROOT)/InvertedIndex.cpp

invertedindextest.o :
	$(COMPILE) ../test/InvertedIndexTest.cpp

trcompare.o :
	$(COMPILE) $(SRCROOT)/compare/TermRecordCompare.cpp

plcompare.o :
	$(COMPILE) $(SRCROOT)/compare/PostingsListCompare.cpp

postingslist.o :
	$(COMPILE) $(SRCROOT)/PostingsList.cpp

simpletokenizer.o :
	$(COMPILE) $(SRCROOT)/util/SimpleTokenizer.cpp

termrecord.o :
	$(COMPILE) $(SRCROOT)/TermRecord.cpp

termidmapping.o :
	$(COMPILE) $(SRCROOT)/TermIDMapping.cpp

termidmapper.o :
	$(COMPILE) $(SRCROOT)/util/TermIDMapper.cpp

ifbdocsupplier.o :
	$(COMPILE) $(SRCROOT)/IndexFileBasedDocSupplier.cpp

document.o :
	$(COMPILE) $(SRCROOT)/Document.cpp

invertedindextest : simpletokenizer.o postingslist.o termrecord.o document.o \
	ifbdocsupplier.o termidmapping.o trcompare.o plcompare.o \
	invertedindex.o invertedindextest.o gtest.o
	$(CC) $(GTESTFLAGS) $(LIBFLAGS) -o $@ $^ 

lexertest : token.o queryexcept.o lexer.o lexertest.o gtest.o
	$(CC) $(GTESTFLAGS) $(LIBFLAGS) -o $@ $^

parsertest : token.o queryexcept.o lexer.o  \
	gtest.o parser.o parsertest.o printvisitor.o astnode.o \
	wordnode.o binaryopnode.o termrecord.o trcompare.o
	$(CC) $(GTESTFLAGS) $(LIBFLAGS) -o $@ $^

clean :
	rm *o search
