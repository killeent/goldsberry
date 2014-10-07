// Original Author: Trevor Killeen (2014)
//
// Simple CLI interface to our Graph ADT. Supports creating a graph and running 
// various algorithms over that graph.

#include <stdio.h>

#include "src/Graph.h"

int main(int argc, char **argv) {
  Graph g = AllocateGraph();
  FreeGraph(g);
  printf("hello\n");
  return 0;
}
