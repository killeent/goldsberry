// Original Author: Trevor Killeen (2014)

#include <stdbool.h>
#include <stdlib.h>

#include "./Graph.h"
#include "./Graph_priv.h"

// Helper function declarations
void FreeEdges(ListItem *vertex);
ListItem *FindVertex(ListItem *vertex, GVertex_t v);
ListItem *FindFirstVertex(ListItem *vertex, GVertex_t v1, GVertex_t v2);
bool AddEdge(ListItem *vertex, GVertex_t v, int w);
void RemoveEdge(ListItem *vertex, GVertex_t v);

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
  EdgeItem *cur, *temp;
  
  for (cur = vertex->neighbors; cur != NULL;) {
    temp = cur->next;
    free(cur);
    cur = temp;  
  }
}

void FreeGraph(Graph g) {
  ListItem *cur, *temp;

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
 for (; vertex != NULL; vertex = vertex->next) {
    if (vertex->data == v) {
      return vertex;
    }
  }
  return NULL;
}

// Loops through the Graph starting at vertex looking for one of the two 
// vertices. Returns a reference to the first of the two vertices it finds, 
// if one of them exists. Otherwise, returns NULL.
ListItem *FindFirstVertex(ListItem *vertex, GVertex_t v1, GVertex_t v2) {
  for (; vertex != NULL; vertex = vertex->next) {
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
  for (neighb = vertex->neighbors; neighb != NULL; neighb = neighb->next) {
    if (neighb->data == v3) {
      return true;
    }
  }

  return false;
}

int GetNeighbors(Graph g, GVertex_t v, Neighbor **out) {
  ListItem *vertex;
  EdgeItem *edge;
  int i;
  
  vertex = FindVertex(g->front, v);
  if (vertex == NULL) {
    // vertex not found
    return -1;  
  }

  if (vertex->count == 0) {
    // vertex has no edges
    return 0;
  }

  *out = (Neighbor *)malloc(sizeof(Neighbor) * vertex->count);
  if (*out == NULL) {
    // memory error
    return -2;
  }

  i = 0;
  for (edge = vertex->neighbors; edge != NULL; edge = edge->next) {
    (*out)[i].v = edge->data;
    (*out)[i].weight = edge->weight;
    i++;
  }
  return vertex->count;
}

// Adds an edge to vertex v with weight w to the vertex stored in li. This
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
  
  // add to front of list
  ei->next = li->neighbors;
  li->neighbors = ei;

  li->count++;
  return true;
}

// Removes the edge pointing to v from the given vertex. This releases
// the memory associated with the edge. If the edge is not found
void RemoveEdge(ListItem *vertex, GVertex_t v) {
  EdgeItem *cur, *temp;

  if (vertex->neighbors == NULL) {
    return;
  }

  // if the edge is at the head of the list, simply update
  // the pointer
  if (vertex->neighbors->data == v) {
    temp = vertex->neighbors;
    vertex->neighbors = vertex->neighbors->next;
    free(temp);
    return;
  }

  cur = vertex->neighbors;
  while (cur->next != NULL) {
    if (cur->next->data == v) {
      // the next thing in the list is the edge we want to remove
      temp = cur->next;
      cur->next = cur->next->next;
      free(temp);
      return;
    }
    cur = cur->next;
  }
}

int AddGraphEdge(Graph g, GVertex_t v1, GVertex_t v2, int w) {
  ListItem *first, *second, *oldBack, *temp;
  bool addedVertex;
 
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
      return -1;
    }

    g->front = first;

    // now create second vertex
    second = (ListItem *)malloc(sizeof(ListItem));
    if (second == NULL) {
      FreeEdges(first); 
      free(first);
      g->front = NULL;
      return -1;
    }

    second->data = v2;

    if (!AddEdge(second, v1, w)) {
      free(second);
      FreeEdges(first);
      free(first);
      g->front = NULL;
      return -1;
    }

    g->back = second;
    g->front->next = g->back;
    return 0;
  }

  // okay we found the first vertex lets add the edge
  if (!AddEdge(first, (first->data == v1) ? v2 : v1, w)) {
    return -1;
  }

  // now find the second vertex
  second = FindFirstVertex(first->next, v1, v2);
  if (second == NULL) {
    // one of the vertices is missing; we need to add it
    second = (ListItem *)malloc(sizeof(ListItem));
    if (second == NULL) {
      // we need to remove the edge we added to the first
      // vertex
      RemoveEdge(first, (first->data == v1) ? v2 : v1);     
      return -1;
    }

    second->data = (first->data == v1) ? v2 : v1;
    // update Graph pointers
    g->back->next = second;
    oldBack = g->back;
    g->back = second;
    addedVertex = true;
  }
  
  // okay we have the second vertex lets add the edge
  if (!AddEdge(second, (second->data == v1) ? v2 : v1, w)) {
    RemoveEdge(first, (first->data == v1 ? v2 : v1));
    // if the second vertex was previously not in the graph, remove it
    if (addedVertex) {
      temp = g->back;
      g->back = oldBack;
      free(temp);
    }
    return -1;
  }
  
  // we made it!
  return 0;
}

void RemoveGraphEdge(Graph g, GVertex_t v1, GVertex_t v2) {
  ListItem *first, *second;

  first = FindFirstVertex(g->front, v1, v2);
  second = FindFirstVertex(first->next, v1, v2);
  // if one or vertices is missing, return immediately
  if (first == NULL || second == NULL) {
    return;
  }

  // okay, remove the edges
  RemoveEdge(first, (first->data == v1) ? v2 : v1);
  RemoveEdge(second, (second->data == v1) ? v2 : v1);
}
