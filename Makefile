CFLAGS=-c -Wall
LIBFLAGS=-lboost_serialization
GTESTFLAGS=-lgtest -lpthread
SRCROOT=../src
INCLUDEROOT=../include
CC=clang++ -std=c++17 -I $(INCLUDEROOT)
COMPILE=$(CC) $(CFLAGS) -o $@

search : main.o 

main.o :
	$(COMPILE) $(SRCROOT)/Main.cpp

tests : 

invertedindextest : simpletokenizer.o postingslist.o termrecord.o document.o \
	ifbdocsupplier.o termidmapping.o trcompare.o plcompare.o \
	invertedindex.o invertedindextest.o gtest.o
	$(CC) $(GTESTFLAGS) $(LIBFLAGS) -o $@ $^ 

rcnvisitor.o:
	$(COMPILE) $(SRCROOT)/query/ast/ResultComputingNodeVisitor.cpp

interpreter.o : 
	$(COMPILE) $(SRCROOT)/query/Interpreter.cpp

parser.o :
	$(COMPILE) $(SRCROOT)/query/Parser.cpp

lexer.o :
	$(COMPILE) $(SRCROOT)/query/Lexer.cpp

gtest.o : 
	$(COMPILE) ../test/gtest_main.cc

invertedindextest.o :
	$(COMPILE) ../test/InvertedIndexTest.cpp

invertedindex.o :
	$(COMPILE) $(SRCROOT)/InvertedIndex.cpp

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

clean :
	rm *o search
