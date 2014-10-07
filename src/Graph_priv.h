// Original Author: Trevor Killeen (2014)
//
// This header file defines the implementation details of the Graph ADT. In
// particular, we chose to represent the Graph as an Adjacency List.

#ifndef _GRAPH_PRIV_H_
#define _GRAPH_PRIV_H_

#include "./Graph.h"

// A vertex is defined by its data, and a pointer to the next vertex. This
// allows us to easily construct an linked list, where the first vertex is
// stored in the adjacency list, and subsequent vertices are nodes to which
// the first vertex is connected.
typedef struct {
  GVertex_t         data;
  struct vertex    *next;
} vertex;

// A Graph adjacency list is an array of Linked Lists of the neighbors of a
// given vertex.
typedef struct graphimpl {
  vertex  *adjlist;
} Graph;

#endif
