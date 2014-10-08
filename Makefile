# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src
TEST = test

all : goldsberry testrunner

goldsberry : goldsberry.o graph.o
	$(CC) $(CFLAGS) -o goldsberry goldsberry.o graph.o

goldsberry.o : goldsberry.c
	$(CC) $(CFLAGS) -c goldsberry.c -o goldsberry.o

graph.o : $(SRC)/Graph.h $(SRC)/Graph_priv.h $(SRC)/Graph.c
	$(CC) $(CFLAGS) -c $(SRC)/Graph.c -o graph.o

testrunner : graph.o testrunner.o graph_test.o
	$(CC) $(CFLAGS) -o testrunner graph.o testrunner.o graph_test.o ~/bin/lib/libcheck.so

testrunner.o : testrunner.c $(TEST)/Graph_test.h
	$(CC) $(CFLAGS) -c testrunner.c -o testrunner.o -I ~/bin/include

graph_test.o : $(SRC)/Graph.h $(SRC)/Graph_priv.h $(TEST)/Graph_test.h $(TEST)/Graph_test.c
	$(CC) $(CFLAGS) -c $(TEST)/Graph_test.c -o graph_test.o -I ~/bin/include

clean:
	/bin/rm -f *.o goldsberry testrunner
