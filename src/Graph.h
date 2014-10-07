// Original Author: Trevor Killeen (2014)
// 
// Represents a weighted, undirected Graph ADT.
//
// A Graph G(V,E) is a set of vertices V and pairs of connected vertices
// {V1,V2} known as edges. Each edge {V1,V2} has an associated weight W that
// is non-negative.

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>  // for bool type

// We define the implementation struct here, and define a Graph as a pointer
// to the implementation. This way we can obscure the implementation details
// from the client.
struct graphimpl;
typedef struct graphimpl *Graph;

// We define the Vertex data type as a integer. We could add support for
// generic data types via a (void *) but the added complexity in terms of
// memory management and vertex comparisons isn't worth it for the scope
// of this project.
typedef int GVertex_t;

// A neighbor is a composed of a vertex and a weight. Thus for any given
// vertex, the outgoing edges from that vertex can represented as a set of
// neighbors.
typedef struct neighb {
  GVertex_t v;
  int       weight;
} Neighbor;

// Allocates a new Graph.
Graph AllocateGraph();

// Frees an existing Graph.
//
// Arguments:
//
//    -- g    the Graph to free.
void FreeGraph(Graph g);

// Tests to see if the Graph contains the given vertex.
//
//    -- g  the Graph to examine.
//    -- v  the vertex to look for
//
// Returns true if the vertex exists in the graph, otherwise false.
bool ContainsVertex(Graph g, GVertex_t v);

// Tests to see if two vertices are adjacent.
//
// Arguments:
//
//    -- g    the Graph to add the edge to.
//    -- v1   the source vertex.
//    -- v2   the destination vertex.
//
// Returns true if there exists an edge {V1,V2}, otherwise false.
bool AreAdjacent(Graph g, GVertex_t v1, GVertex_t v2);

// Gets a list of neighbors for a given vertex.
//
// Arguments:
//
//    -- g    the Graph to query.
//    -- v    the vertex to get neighbors from.
//    -- out  pointer to a location where we can store the neighbors.
//
// Returns -1 if the passed vertex isn't in the Graph, 0 if it has no neighbors,
// otherwise 1. In the later casereturns array of Neighbors in the location specified
// by out. The client is responsible for free()'ing this array.
int GetNeighbors(Graph g, GVertex_t v, Neighbor **out);

// Adds an edge between two vertices. If either of the vertices is not
// present in the Graph, they are automatically added.
//
// Arguments:
//
//    -- g    the Graph to add the edge to.
//    -- v1   the source vertex.
//    -- v2   the destination vertex.
//    -- w    the weight of the edge.
//
// Returns void.
void AddGraphEdge(Graph g, GVertex_t v1, GVertex_t v2, int w);

// Removes an edge between vertices.
//
// Arguments:
//
//    -- g    the Graph to add the edge to.
//    -- v1   the source vertex.
//    -- v2   the destination vertex.
//
// Returns -1 if either of the vertices is not present in the graph,
// otherwise returns 0.
int RemoveGraphEdge(Graph g, GVertex_t v1, GVertex_t v2);

#endif
