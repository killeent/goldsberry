// Original Author: Trevor Killeen (2014)
//
// This header file defines the implementation details of the Graph ADT. In
// particular, we chose to represent the Graph as an Adjacency List.

#ifndef _GRAPH_PRIV_H_
#define _GRAPH_PRIV_H_

#include "./Graph.h"

// A vertex is defined by its data, and a pointer to the next vertex. This
// allows us to easily construct an linked list of vertices.
typedef struct {
  GVertex_t         data;
  struct vertex    *next;
} vertex;

// A listitem is composed of:
//
// 1. A Vertex (as represented by its data value).
// 2. The list of vertices that vertex has edges to (the adjacency list).
// 3. The count of vertices that vertex has edges to. 
// 4. A pointer to the next item in the list.
typedef struct {
  GVertex_t         data;
  vertex           *adjlist;
  int               count;   
  struct listitem  *next;
} listitem;

// A Graph represented as an adjacency list is a list of vertices and the vertices
// to which they have edges to.
typedef struct graphimpl {
  listitem *adjlist;
} Graph;

#endif
