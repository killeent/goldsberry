// Original Author: Trevor Killeen (2014)

#include <stdbool.h>
#include <stdlib.h>

#include "./Graph.h"
#include "./Graph_priv.h"

// Helper function declarations
void FreeEdges(ListItem *vertex);
ListItem *FindVertex(Graph g, GVertex_t v);
ListItem *FindFirstVertex(ListItem *vertex, GVertex_t v1, GVertex_t v2);
bool AddEdge(ListItem *vertex, GVertex_t v, int w);

Graph AllocateGraph() {
  Graph g;
  
  g = (Graph) malloc(sizeof(GraphImplementation));
  if (g == NULL) {
    return NULL;

  }
  return g;
}

// Releases memory associated with the edge list of a given vertex.
void FreeEdges(ListItem *vertex) {
  EdgeItem *cur, temp;
  
  for (cur = vertex->neighbors; cur != NULL;) {
    temp = cur->next;
    free(cur);
    cur = temp;  
  }
}

void FreeGraph(Graph g) {
  ListItem *cur, temp;

  for (cur = g->front; cur != NULL;) {
    FreeEdges(cur);
    temp = cur->next;
    free(cur);
    cur = temp;
  }
}

// Loops through the Graph looking for the given vertex. Returns a reference
// to that vertex if it exists. Otherwise, returns NULL.
ListItem *FindVertex(ListItem *vertex, GVertex_t v) {
  for (vertex = g->adjvertexist; vertex != NULL; vertex = vertex->next) {
    if (vertex->data == v) {
      return vertex;
    }
  }
  return NULL;
}

// Loops through the Graph starting at llooking for one of the two vertices. 
// Returns a reference to the first of the two vertices it finds, if one of 
// them exists. Otherwise, returns NULL.
ListItem *FindFirstVertex(ListItem *vertex, GVertex_t v1, GVertex_t v2) {
  for (vertex = g->front; vertex != NULL; vertex = vertex->next) {
    if (vertex->data == v1 || vertex-> data == v2) {
      return vertex;
    }
  }
  return NULL;
}

bool ContainsVertex(Graph g, GVertex_t v) {
  return FindVertex(g->front, v) != NULL ? true : false;
}

bool AreAdjacent(Graph g, GVertex_t v1, GVertex_t v2) {
  ListItem *vertex; 
  EdgeItem *neighb;
  GVertex_t v3;

  vertex = FindFirstVertex(g->front, v1, v2);
  if (vertex == NULL) {
    return false;
  } 

  // determine which of the two vertices we found, so we can
  // look for the other.
  v3 = (vertex->data == v1) ? v2 : v1;

  // now loop through the edges

  for (neighb = vertex->neighbors; neighb != NULL; neighb = neigbh->next) {
    if (neighb->data == v3) {
      return true;
    }
  }

  return false;
}

int GetNeighbors(Graph g, GVertex_t v, Neighbor **out) {
  ListItem *vertex;
  EdgeItem *neighb;
  int i;
  
  vertex = FindVertex(g->front, v1);
  if (vertex == NULL) {
    return -1;  
  }
  if (vertex->count == 0) {
    return 0;
  }
  *out = (Neighbor *)malloc(sizeof(Neighbor)*vertex->count);
  if (*out == NULL) {
    return -2;
  }
  i = 0;
  for (neighb = vertex->neighbors; neighb != NULL; neighb = neighb->next) {
    out[i].v = neighb.data;
    out[i].weight = neighb.weight;
    i++;
  }
  return vertex->count;
}

// Adds and edge to vertex v with weight w to the vertex stored in li. This
// function does not check to see if the vertex is already in the list. It
// merely inserts the new edge at the front of the list of neighbors.
//
// Returns true if successful, false if an out of memory error occurs.
bool AddEdge(ListItem *li, GVertex_t v, int w) {
  EdgeItem *ei;
  ei = (EdgeItem *)malloc(sizeof(EdgeItem));
  if (ei == NULL) {
    return false;  
  }
  ei->data = v;
  ei->weight = w;
  ei->next = li->neighbors;
  li->neighbors = ei;
  li->count++;
  return true;
}

void AddGraphEdge(Graph g, GVertex_t v1, GVertex_t v2, int w) {
  ListItem *first, second;
  EdgeItem *ei;
 
  // try to find the first vertex in the list
  first = FindFirstVertex(g->front, v1, v2);

  // handle the corner case where the graph is empty
  if (first == NULL) {
    // create first vertex and edge
    first = (ListItem *)malloc(sizeof(ListItem));
    if (first == NULL) {
      // first malloc, so nothing to clean here
      return -1;
    }
    first->data = v1;
    if (!AddEdge(first, v2, w)) {
      free(first);
    }
    g->front = first;
    // now create second vertex
    second = (ListItem *)malloc(sizeof(ListItem));
    if (second == NULL) {

      free(first);
      g->front = NULL;
    }
    second->data = v2;
    if (!AddEdge(second, v1, w)) {
      // mem error
    }
    g->back = second;
    g->front->next = g->back;
    return 0;
  }

  // okay we found the first vertex lets add the edge
  if (!AddEdge(first, (first->data == v1) ? v2 : v1, w)) {
    // mem error
  }

  // now find the second vertex
  second = FindFirstVertex(first->next, v1, v2);
  if (second == NULL) {
    // one of the vertices is missing; we need to add it
    second = (ListItem *)malloc(sizeof(ListItem));
    if (second == NULL) {
      // mem error
    }
    second->data = (first->data == v1) ? v2 : v1;
    // update Graph pointers
    g->back->next = second;
    g->back = second;
  }
  
  // okay we have the second vertex lets add the edge
  if (!AddEdge(second, (second->data == v1) ? v2 : v1, w)) {
    // mem error
  }
  
  // we made it!
  return 0;
}
