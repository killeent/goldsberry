// Original Author: Trevor Killeen (2014)

#include <stdbool.h>
#include <stdlib.h>

#include "./Graph.h"
#include "./Graph_priv.h"

// Helper function declarations
void FreeEdges(ListItem *vertex);
ListItem *FindVertex(ListItem *vertex, GVertex_t v);
ListItem *FindFirstVertex(ListItem *vertex, GVertex_t v1, GVertex_t v2);
int AddVertexSaveBack(Graph g, GVertex_t v, ListItem **back);
bool AddEdge(ListItem *vertex, GVertex_t v, int w);
void RemoveEdge(ListItem *vertex, GVertex_t v);
int AddGraphEdgeEmptyGraph(Graph g, GVertex_t v1, GVertex_t v2, int w);

Graph AllocateGraph() {
  Graph g;
  
  g = (Graph) malloc(sizeof(GraphImplementation));
  if (g == NULL) {
    return NULL;
  }
  g->front = g->back = NULL;

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

  free(g);
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

// Adds a new vertex to the back of the list. Places a pointer to the old back
// of the list in old if a Vertex is added, else is NULL. Otherwise, follows the 
// conventions of AddVertex defined in Graph.h.
int AddVertexSaveBack(Graph g, GVertex_t v, ListItem **old) {
  ListItem *l;

  if ((l = FindVertex(g->front, v)) != NULL) {
    // already exists!
    *old = NULL;
    return 0;
  }

  l = (ListItem *)malloc(sizeof(ListItem));
  if (l == NULL) {
    return -1;
  }

  l->data = v;
  l->neighbors = NULL;
  l->count = 0;
  l->next = NULL;

  *old = g->back;

  // case 1: graph empty, set as front and back 
  if (g->front == NULL) {
    g->front = g->back = l;
    return 0;
  }

  // case 2: append to end
  g->back->next = l;
  g->back = l;
  return 0;
}

// adds new vertex to the back of the list
int AddVertex(Graph g, GVertex_t v) {
  ListItem *l;
  return AddVertexSaveBack(g, v, &l);
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
    vertex->count--;
    return;
  }

  cur = vertex->neighbors;
  while (cur->next != NULL) {
    if (cur->next->data == v) {
      // the next thing in the list is the edge we want to remove
      temp = cur->next;
      cur->next = cur->next->next;
      free(temp);
      vertex->count--;
      return;
    }
    cur = cur->next;
  }
}

int AddGraphEdge(Graph g, GVertex_t v1, GVertex_t v2, int w) {
  ListItem *first, *second, *oldBackFirst, *oldBackSecond;
  bool addedFirst, addedSecond;
  int ret;

  // handle empty graph
  if (g->front == NULL) {
    return AddGraphEdgeEmptyGraph(g, v1, v2, w);
  }
 
  // try to find the first vertex in the list
  first = FindFirstVertex(g->front, v1, v2);

  if (first == NULL) {
    // neither vertex is in the graph. Add one 
    ret = AddVertexSaveBack(g, v1, &oldBackFirst);
    if (ret == -1) {
      return -1;  
    }
    first = g->back;
    addedFirst = true;
  }

  // okay now we are guarantted to have the first vertex lets add the edge
  if (!AddEdge(first, (first->data == v1) ? v2 : v1, w)) {
    // on memory error, if first vertex was previously not in the graph, remove it
    if (addedFirst) {
      g->back = oldBackFirst; 
      g->back->next = NULL;
      free(first);
    }
    return -1;
  }

  // now find the second vertex
  second = FindFirstVertex(first->next, v1, v2);
  if (second == NULL) {
    // the second vertex is missing; we need to add it
    ret = AddVertexSaveBack(g, v2, &oldBackSecond);
    if (ret == -1) {
      // we need to remove the edge we added to the first
      // vertex
      RemoveEdge(first, (first->data == v1) ? v2 : v1);     
      if (addedFirst) {
        g->back = oldBackFirst;
        g->back->next = NULL;
        free(first);
      }
      return -1;
    }
    second = g->back;
    addedSecond = true;
  }
  
  // okay we have the second vertex lets add the edge
  if (!AddEdge(second, (second->data == v1) ? v2 : v1, w)) {
    RemoveEdge(first, (first->data == v1 ? v2 : v1));
    // handle each of two cases -> we added both vertices, or we added
    // only the second. 
    if (addedFirst && addedSecond) {
        g->back = oldBackFirst;
        g->back->next = NULL;
        free(first);
        free(second);
    } else if (addedSecond) {
      g->back = oldBackSecond;
      g->back->next = NULL;
      free(second);
    }
    return -1;
  }
  
  // we made it!
  return 0;
}

// helper function to add an edge to a previously empty Graph.
int AddGraphEdgeEmptyGraph(Graph g, GVertex_t v1, GVertex_t v2, int w) {
  ListItem *first, *second;
  int ret;

  // create first vertex and edge
  ret = AddVertex(g, v1);
  if (ret == -1) {
    return -1;
  }
  first = g->back;

  // add edge to v2
  if (!AddEdge(first, v2, w)) {
    free(first);
    return -1;
  }
  
  // now add second vertex
  ret = AddVertex(g, v2);
  if (ret == -1) {
    FreeEdges(first); 
    free(first);
    g->front = NULL;
    return -1;
  }
  second = g->back;

  // add edge to v1
  if (!AddEdge(second, v1, w)) {
    free(second);
    FreeEdges(first);
    free(first);
    g->front = g->back = NULL;
    return -1;
  }

  return 0;
}

void RemoveGraphEdge(Graph g, GVertex_t v1, GVertex_t v2) {
  ListItem *first, *second;

  // if graph is empty, or single element, return immediately
  if (g->front == NULL || g->front == g->back) {
    return;
  }

  first = FindFirstVertex(g->front, v1, v2);
  second = FindFirstVertex(first->next, v1, v2);
  // if one or vertices is missing, return 
  if (first == NULL || second == NULL) {
    return;
  }

  // okay, remove the edges
  RemoveEdge(first, (first->data == v1) ? v2 : v1);
  RemoveEdge(second, (second->data == v1) ? v2 : v1);
}
