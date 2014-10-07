# compiler and flags
CC = gcc
CFLAGS = -g -Wall -std=gnu11 -O3

# folders
SRC = src

goldsberry : goldsberry.o graph.o
	$(CC) $(CFLAGS) -o goldsberry goldsberry.o graph.o

goldsberry.o : goldsberry.c
	$(CC) $(CFLAGS) -c goldsberry.c -o goldsberry.o

graph.o : $(SRC)/Graph.h $(SRC)/Graph_priv.h $(SRC)/Graph.c
	$(CC) $(CFLAGS) -c $(SRC)/Graph.c -o graph.o

clean:
	/bin/rm *.o goldsberry
