// Original Author: Trevor Killeen (2014)
//
// This header file defines the implementation details of the Graph ADT. In
// particular, we chose to represent the Graph as an Adjacency List.

#ifndef _GRAPH_PRIV_H_
#define _GRAPH_PRIV_H_

#include "./Graph.h"

// For any given vertex, we want to represent the vertices to which it
// has edges to, and the weights of those connections. We encapsulate
// this information in a linked list of 'EdgeItem's, which store
// vertex/weight pairs, along with references to the next item in the list.
// Thus we can easily encapsulate the outgoing edges for any vertex by
// constructing a chain of EdgeItems.
typedef struct {
  GVertex_t         data;
  int               weight;
  struct EdgeItem  *next;
} EdgeItem;

// A listitem is composed of:
//
// 1. A Vertex (as represented by its data value).
// 2. The list of vertices that vertex has edges to.
// 3. The count of vertices that vertex has edges to. 
// 4. A pointer to the next item in the list.
typedef struct litem {
  GVertex_t         data;
  EdgeItem         *neighbors;
  int               count;   
  struct litem     *next;
} ListItem;

// A Graph represented as an adjacency list is a list of vertices and the 
// vertices to which they have edges to. Our implementation is a simple Linked 
// List of Linked Lists. 
//
// In practice, we would probably prefer to have a Hash
// Table of vertices for better perf. However, since this project is mostly
// for learning and will not be operating on large data sets, the overhead
// involved to implement a Hash Table is not worth it.
typedef struct graphimpl {
  ListItem *adjlist;
} GraphImplementation;

#endif
