// Original Author: Trevor Killeen (2014)
// 
// A Graph G(V,E) is a set of vertices V and pairs of connected vertices
// {V1,V2} known as edges. 

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stdbool.h>  // for bool type

// We define the implementation struct here, and define a Graph as a pointer
// to the implementation. This way we can obscure the implementation details
// from the client.
struct graphimpl;
typedef struct graphimpl *Graph;

// We define the Vertex data type as a void pointer, it is up to the client
// to maintain proper homogeneity of types in the Graph. For now, we only
// support types that can be compared via the '==' operator. 
typedef void *GVertex_t;

// Allocates a new Graph.
Graph AllocateGraph();

// Frees an existing Graph.
//
// Arguments:
//
//    -- g    the Graph to free.
//
// Returns void.
void FreeGraph(Graph g);

int 

// Adds an edge between two vertices. If either of the vertices is not
// present in the Graph, they are automatically added.
//
// Arguments:
//
//    -- g    the Graph to add the edge to.
//    -- v1   the source vertex.
//    -- v2   the destination vertex.
//
// Returns void.
void AddGraphEdge(Graph g, GVertex_t v1, GVertex_t v2);

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
