// Original Author: Trevor Killeen (2014)
//
// Simple CLI interface to our Graph ADT. Supports creating a graph and running 
// various algorithms over that graph.

#include <stdio.h>

#include "src/Graph.h"

int main() {
  Graph g = AllocateGraph();
  FreeGraph(g);
  return 0;
}
