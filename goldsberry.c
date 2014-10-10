// Original Author: Trevor Killeen (2014)
//
// Simple CLI interface to our Graph ADT. Supports creating a graph and running 
// various API operations over that graph.

#include <stdio.h>

#include "src/Graph.h"

#define BUF_SIZE 24

void help() {
  printf("Commands:\n\n");
  printf("add x => adds vertex with value x to the Graph\n");
  printf("contains x => returns whether x is present in the Graph\n");
  printf("adj x y => returns whether there exists an edge from x to y in the Graph\n");
  printf("edge x y w => adds an edge between x and y with weight w to the Graph\n");
  printf("remove x y => removes an edge between x and y from the Graph\n");
  printf("neighbors x => lists a series of (y,w) pairs, where each y is a neighbor of x and w is the weight of the edge between them\n"); 
  printf("help => show this menu\n");
  printf("quit => quit the application\n");
}

void error() {
  printf("invalid command\n");
}

// Parses the user input string, calling the appropriate function or
// printing an error if an invalid command is used. Returns true if
// we should prompt for another command, false if we should quit.
bool parseInput(char *input) {
  return false; 
}

int main(int argc, char **argv) {
  Graph g;
  char buf[BUF_SIZE];

  g = AllocateGraph();
  if (g == NULL) {
    return 1;
  }

  printf("Hello! Welcome to Goldsberry. Type 'help' for help.\n");

  while(1) {
    fgets(buf, BUF_SIZE, stdin);
    if (!parseInput(buf)) {
      break;
    }

  }
  FreeGraph(g);
  return 0;
}
