CC=clang++ -std=c++17
CFLAGS=-c -Wall
LIBFLAGS=-lboost_serialization
GTESTFLAGS=-lgtest -lpthread

search : main.o 
	$(CC) $(LIBFLAGS) main.o -o search

main.o : invertedindex.o interpreter.o 
	$(CC) $(CFLAGS) invertedindex.o interpreter.o Main.cpp -o main.o

tests : 

invertedindex.o :

termidmapping.o :

interpreted.o : 

lexer.o :

parser.o :



clean :
	rm *o search
