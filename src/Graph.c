// Original Author: Trevor Killeen (2014)

#include <stdbool.h>
#include <stdlib.h>

#include "./Graph.h"
#include "./Graph_priv.h"

// Helper function declarations
ListItem *FindVertex(Graph g, GVertex_t v);
ListItem *FindFirstVertex(ListItem *l, GVertex_t v1, GVertex_t v2);
int AddEdge(ListItem *li, GVertex_t v, int w);

Graph AllocateGraph() {
  Graph g;
  
  g = (Graph) malloc(sizeof(GraphImplementation));
  if (g == NULL) {
    return NULL;

  }
  return g;
}

void FreeGraph(Graph g) {
}

// Loops through the Graph looking for the given vertex. Returns a reference
// to that vertex if it exists. Otherwise, returns NULL.
ListItem *FindVertex(Graph g, GVertex_t v) {
  ListItem *l;
  for (l = g->adjlist; l != NULL; l = l->next) {
    if (l->data == v) {
      return l;
    }
  }
  return NULL;
}

// Loops through the Graph starting at llooking for one of the two vertices. 
// Returns a reference to the first of the two vertices it finds, if one of 
// them exists. Otherwise, returns NULL.
ListItem *FindFirstVertex(ListItem *l, GVertex_t v1, GVertex_t v2) {
  for (l = g->front; l != NULL; l = l->next) {
    if (l->data == v1 || l-> data == v2) {
      return l;
    }
  }
  return NULL;
}

bool ContainsVertex(Graph g, GVertex_t v) {
  return FindVertex(g->front, v) != NULL ? true : false;
}

bool AreAdjacent(Graph g, GVertex_t v1, GVertex_t v2) {
  ListItem *l1; 
  EdgeItem *neighb;
  GVertex_t v3;

  l1 = FindFirstVertex(g->front, v1, v2);
  if (l1 == NULL) {
    return false;
  } 

  // determine which of the two vertices we found, so we can
  // look for the other.
  v3 = (li->data == v1) ? v2 : v1;

  // now loop through the edges

  for (neighb = li->neighbors; neighb != NULL; neighb = neigbh->next) {
    if (neighb->data == v3) {
      return true;
    }
  }

  return false;
}

int GetNeighbors(Graph g, GVertex_t v, Neighbor **out) {
  ListItem *li;
  EdgeItem *neighb;
  int i;
  
  li = FindVertex(g->front, v1);
  if (li == NULL) {
    return -1;  
  }
  if (li->count == 0) {
    return 0;
  }
  *out = (Neighbor *)malloc(sizeof(Neighbor)*li->count);
  if (*out == NULL) {
    // TODO: some sort of graceful memory error
  }
  i = 0;
  for (neighb = li->neighbors; neighb != NULL; neighb = neighb->next) {
    out[i].v = neighb.data;
    out[i].weight = neighb.weight;
    i++;
  }
  return li->count;
}

// Adds and edge to vertex v with weight w to the vertex stored in li. This
// function does not check to see if the vertex is already in the list. It
// merely inserts the new edge at the front of the list of neighbors.
//
// Returns 1 if successful, 0 if an out of memory error occurs.
int AddEdge(ListItem *li, GVertex_t v, int w) {
  EdgeItem *ei;
  ei = (EdgeItem *)malloc(sizeof(EdgeItem));
  if (ei == NULL) {
    return 0;  
  }
  ei->data = v;
  ei->weight = w;
  ei->next = li->neighbors;
  li->neighbors = ei;
  li->count++;
  return 1;
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
      // mem error
    }
    first->data = v1;
    if (!AddEdge(first, v2, w)) {
      // mem error
    }
    g->front = first;
    // now create second vertex
    second = (ListItem *)malloc(sizeof(ListItem));
    if (second == NULL) {
      // mem error 
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
