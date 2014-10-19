// Original Author: Trevor Killeen (2014)
//
// Simple CLI interface to our Graph ADT. Supports creating a graph and running 
// various API operations over that graph.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "src/Graph.h"

#define BUF_SIZE 24

// displays commands to the user
void help() {
  printf("Commands (x, y and w must be integers):\n\n");
  printf("add x => adds vertex with value x to the Graph\n");
  printf("contains x => returns whether x is present in the Graph\n");
  printf("adj x y => returns whether there exists an edge from x to y in the Graph\n");
  printf("edge x y w => adds an edge between x and y with weight w to the Graph\n");
  printf("remove x y => removes an edge between x and y from the Graph\n");
  printf("neighbors x => lists a series of (y,w) pairs, where each y is a neighbor of x and w is the weight of the edge between them\n"); 
  printf("help => show this menu\n");
  printf("quit => quit the application\n");
}

// functions associated with the commands the user can call

void add(Graph g, int x) {
  AddVertex(g, x);
}

void contains(Graph g, int x) {
  if (ContainsVertex(g, x)) {
    printf("the graph contains %d\n", x);
  } else {
    printf("the graph does not contain %d\n", x);
  }
}

void adj(Graph g, int x, int y) {
  if (AreAdjacent(g, x, y)) {
    printf("%d and %d are neighbors\n", x, y);
  } else {
    printf("%d and %d are not neighbors\n", x, y);
  }
}

void addEdge(Graph g, int x, int y, int w) {
  AddGraphEdge(g, x, y, w);
}

void removeEdge(Graph g, int x, int y) {
  RemoveGraphEdge(g, x, y);
}

void neighbors(Graph g, int x) {
  Neighbor *out;
  Neighbor nb;
  int i, ret;
  
  ret = GetNeighbors(g, x, &out);
  if (ret == -1) {
    printf("%d is not in the graph\n", x);
  } else if (ret == 0) {
    printf("%d has no neighbors\n", x);
  } else {
    printf("%d has edges to:", x);
    for (i = 0; i < ret;  i++) {
      nb = out[i];
      printf(" (%d, weight: %d)", nb.v, nb.weight);
    }
    printf("\n");
  }
  free(out);
}

void error(char *msg) {
  printf("error: %s\n", msg);
}

// Unsafe integer extraction functions incoming! Because this is a small
// personal project so atoi!, atoi!, atoi!

// helper function to extract one int from a user-input string
// using strtok and atoi. Assumesthe the client has already called
// strtok for the first time. Returns true if int extracted, placing
// it in the location specified by out. Otherwise returns false.
bool extractOneInt(int *out) {
    char *str;

    str = strtok(NULL, " ");
    if (str == NULL) {
      return false;
    }
    *out = atoi(str);

    return true;
}

// helper function to extract two ints, in a similar fashion
bool extractTwoInts(int *out1, int *out2) {
    char *str;

    str = strtok(NULL, " ");
    if (str == NULL) {
      return false;
    }
    *out1 = atoi(str);
    return extractOneInt(out2);
}

// helper function to extract three ints, in the same way!
bool extractThreeInts(int *out1, int *out2, int *out3) {
    char *str;

    str = strtok(NULL, " ");
    if (str == NULL) {
      return false;
    }
    *out1 = atoi(str);
    return extractTwoInts(out2, out3);
}

// Parses the user input string, calling the appropriate function or
// printing an error if an invalid command is used. Returns true if
// we should prompt for another command, false if we should quit.
bool parseInput(Graph g, char *input) {
  int x = 0, y = 0, w = 0;
  char *split;
  bool should_exit = false;

  // remove trailing newline
  split = strtok(input, "\n");

  split = strtok(input, " ");
  if (split == NULL) {
    error("unknown command");
    return should_exit;
  }
  
  // gross if/else ladder to figure out what function to call and
  // verify proper input to that function
  if (strcmp(split, "add") == 0) {
    if (!extractOneInt(&x)) {
      error("invalid arguments to add");
    }
    add(g, x);
  } else if (strcmp(split, "contains") == 0) {
    if (!extractOneInt(&x)) {
      error("invalid arguments to contains");
    }
    contains(g, x);
  } else if (strcmp(split, "adj") == 0) {
    if (!extractTwoInts(&x, &y)) {
      error("invalid arguments to adj");
    }
    adj(g, x, y);
  } else if (strcmp(split, "edge") == 0) {
    if (!extractThreeInts(&x, &y, &w)) {
      error("invalid arguments to edge");
    }
    addEdge(g, x, y, w);
  } else if (strcmp(split, "remove") == 0) {
    if (!extractTwoInts(&x, &y)) {
      error("invalid argument to remove");
    }
    removeEdge(g, x, y);
  } else if (strcmp(split, "neighbors") == 0) {
    // try to get the vertex it wants
    if (!extractOneInt(&x)) {
      error("invalid argument to neighbors");
    }
    neighbors(g, x); 
  } else if (strcmp(split, "help") == 0) {
    help();
  } else if (strcmp(split, "quit") == 0) {
    should_exit = true;
  } else {
    error("invalid command");
  }

  return should_exit;
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
    if (parseInput(g, buf)) {
      break;
    }

  }
  
  printf("Exiting\n");

  FreeGraph(g);
  return 0;
}
