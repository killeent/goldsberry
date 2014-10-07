// Original Author: Trevor Killeen (2014)

#include <stdbool.h>
#include <stdlib.h>

#include "./Graph.h"
#include "./Graph_priv.h"

// Helper function declarations
ListItem *FindVertex(Graph g, GVertex_t v); 

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

bool ContainsVertex(Graph g, GVertex_t v) {
  return FindVertex(g, v) != NULL ? true : false;
}

bool AreAdjacent(Graph g, GVertex_t v1, GVertex_t v2) {
  ListItem *l1; 
  EdgeItem *neighb;

  l1 = FindVertex(g, v1);
  if (l1 == NULL) {
    return false;
  } 

  // now loop through the edges
  for (neighb = li->neighbors; neighb != NULL; neighb = neigbh->next) {
    if (neighb->data == v2) {
      return true;
    }
  }

  return false;
}

int GetNeighbors(Graph g, GVertex_t v, Neighbor **out) {
  ListItem *li;
  EdgeItem *neighb;
  int i;
  
  li = FindVertex(g, v1);
  if (li == NULL) {
    return -1;  
  }
  if (li->count == 0) {
    return 0;
  }
  *out = (Neighbor *)malloc(sizeof(Neighbor)*li->count);
  i = 0;
  for (neighb = li->neighbors; neighb != NULL; neighb = neighb->next) {
    out[i].v = neighb.data;
    out[i].weight = neighb.weight;
    i++;
  }
  return li->count;
}
