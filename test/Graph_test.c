// Original Author: Trevor Killeen (2014)
//
// Test Suite for the Graph ADT and adjacency list implementation.

#include <check.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./Graph_test.h"
#include "../src/Graph.h"
#include "../src/Graph_priv.h"

// Helper function declarations.
bool ContainsNeighbor(Neighbor *, int, GVertex_t, int);

// Allocate a Graph on setup, Free it on teardown

Graph g;

void setup() {
  g = AllocateGraph();
  ck_assert(g != NULL);
}

void teardown() {
  FreeGraph(g);
}

// Basic test that Graph Allocation and Free'ing does not crash. This *does
// not* test for memory leaks. 
START_TEST(alloc_test)
{
}
END_TEST

// Tests operations on an empty graph, verifying that they do not
// cause crashes.
START_TEST(empty_graph_test)
{
  Neighbor *out;

  ck_assert(!ContainsVertex(g, 0));
  ck_assert(!AreAdjacent(g, 0, 1));
  ck_assert(GetNeighbors(g, 0, &out) == -1);
  RemoveGraphEdge(g, 0, 1);
}
END_TEST

// Tests adding a single vertex to the Graph.
START_TEST(single_vertex_test) 
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(ContainsVertex(g, 1));
}
END_TEST

// Tests adding a single edge to the an empty Graph. Checks that 
//
// 1. ContainsVertex returns true
// 2. AreAdjacent returns true
START_TEST(single_edge_empty_graph_test)
{
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 

  ck_assert(ContainsVertex(g, 1));
  ck_assert(ContainsVertex(g, 2));
  ck_assert(AreAdjacent(g, 1, 2));
  ck_assert(AreAdjacent(g, 2, 1)); 
}
END_TEST

// Tests removing the only edge from a Graph.
START_TEST(single_edge_removal_test) 
{
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0);
  RemoveGraphEdge(g, 1, 2);

  ck_assert(!AreAdjacent(g, 1, 2));
  ck_assert(ContainsVertex(g, 1));
  ck_assert(ContainsVertex(g, 2));
}
END_TEST

// Tests removing a nonexistant edge from the Graph (tests for not crashing)
START_TEST(missing_edge_removal_test) 
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  RemoveGraphEdge(g, 1, 2);
}
END_TEST;

// Tests removing a nonexistant edge from the Graph where one of
// the vertices is missing (tests for not crashing)
START_TEST(missing_edge_and_vertex_removal_test) 
{
  ck_assert(AddVertex(g, 1) != -1);
  RemoveGraphEdge(g, 1, 2);
}
END_TEST;

// Tests adding an edge to the graph where one vertex is
// already present.
START_TEST(single_edge_one_vertex_present_test)
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 

  ck_assert(ContainsVertex(g, 1));
  ck_assert(ContainsVertex(g, 2));
  ck_assert(AreAdjacent(g, 1, 2));
  ck_assert(AreAdjacent(g, 2, 1)); 
}
END_TEST

// Tests adding an edge to the graph where both vertices are present.
START_TEST(single_edge_both_vertices_present_test)
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 

  ck_assert(ContainsVertex(g, 1));
  ck_assert(ContainsVertex(g, 2));
  ck_assert(AreAdjacent(g, 1, 2));
  ck_assert(AreAdjacent(g, 2, 1)); 
}
END_TEST

// Tests adding an edges to the graph where both vertices are present in
// addition to a number of other vertices. 
START_TEST(multiple_edges_populated_graph_test)
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddVertex(g, 5) != -1);
  ck_assert(AddVertex(g, 3) != -1);
  ck_assert(AddVertex(g, 9) != -1);
  ck_assert(AddVertex(g, 7) != -1);
  ck_assert(AddGraphEdge(g, 5, 3, 0) == 0); 
  ck_assert(AddGraphEdge(g, 7, 1, 0) == 0);

  ck_assert(AreAdjacent(g, 5, 3));
  ck_assert(AreAdjacent(g, 7, 1)); 
}
END_TEST

// Tests adding multiple edges to a single vertex.
START_TEST(multiple_edges_from_single_vertex_test)
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddVertex(g, 5) != -1);
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 
  ck_assert(AddGraphEdge(g, 1, 5, 0) == 0);

  ck_assert(AreAdjacent(g, 1, 2));
  ck_assert(AreAdjacent(g, 1, 5));
}
END_TEST

// Tests removing multiple edges from a single vertex.
START_TEST(remove_multiple_edges_from_single_vertex_test)
{
  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddVertex(g, 5) != -1);
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 
  ck_assert(AddGraphEdge(g, 1, 5, 0) == 0);
  RemoveGraphEdge(g, 1, 2);
  RemoveGraphEdge(g, 1, 5);

  ck_assert(!AreAdjacent(g, 1, 2));
  ck_assert(!AreAdjacent(g, 1, 5));
}
END_TEST

// Tests trying to get the neighbors from a vertex not in the Graph.
START_TEST(get_neighbors_missing_vertex_test)
{
  Neighbor *out;

  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(GetNeighbors(g, 3, &out) == -1);
}
END_TEST

// Tests trying to get the neighbors from a vertex with no neighbors.
START_TEST(get_neighbors_no_neighbors_test) 
{
  Neighbor *out;

  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(GetNeighbors(g, 1, &out) == 0);
}
END_TEST

// Tests trying to get the neighbors from a vertex with a single neighbor.
START_TEST(get_neighbors_single_neighbor_test) 
{
  Neighbor *out;

  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 
  ck_assert(GetNeighbors(g, 1, &out) == 1);

  ck_assert(ContainsNeighbor(out, 1, 2, 0));
  free(out);
}
END_TEST

// Tests trying to get the neighbors from a vertex with multiple neighbors.
START_TEST(get_neighbors_multiple_neighbors_test)
{
  Neighbor *out;

  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddVertex(g, 5) != -1);
  ck_assert(AddGraphEdge(g, 1, 2, 1) == 0); 
  ck_assert(AddGraphEdge(g, 1, 5, 5) == 0);

  ck_assert(GetNeighbors(g, 1, &out) == 2);
  ck_assert(ContainsNeighbor(out, 2, 2, 1));
  ck_assert(ContainsNeighbor(out, 2, 5, 5));
  free(out);
}
END_TEST

// Tests a series of interleaved add vertex, add edge and add remove operations.
START_TEST(pseudo_end_to_end_test)
{
  Neighbor *out;
  int i;

  ck_assert(AddVertex(g, 1) != -1);
  ck_assert(AddVertex(g, 2) != -1);
  ck_assert(AddVertex(g, 3) != -1);
  ck_assert(AddVertex(g, 4) != -1);
  ck_assert(AddVertex(g, 5) != -1);
  ck_assert(AddVertex(g, 6) != -1);
  ck_assert(AddVertex(g, 7) != -1);
  ck_assert(AddVertex(g, 8) != -1);

  ck_assert(AddGraphEdge(g, 9, 10, 0) == 0);
  ck_assert(AddGraphEdge(g, 6, 3, 0) == 0);
  ck_assert(AddGraphEdge(g, 3, 10, 0) == 0);
  ck_assert(AddGraphEdge(g, 1, 5, 0) == 0);
  ck_assert(AddGraphEdge(g, 4, 2, 1) == 0);
  ck_assert(AddGraphEdge(g, 4, 3, 1) == 0);
  ck_assert(AddGraphEdge(g, 4, 5, 1) == 0);
  ck_assert(AddGraphEdge(g, 8, 1, 2) == 0);
  ck_assert(AddGraphEdge(g, 9, 2, 2) == 0);

  // Tests everything up to this point
  for (i = 1; i <= 10; i++) {
    ck_assert(ContainsVertex(g, i));
  }
  ck_assert(AreAdjacent(g, 9, 10));
  ck_assert(AreAdjacent(g, 6, 3));
  ck_assert(AreAdjacent(g, 3, 10));
  ck_assert(AreAdjacent(g, 1, 5));
  ck_assert(AreAdjacent(g, 4, 2));
  ck_assert(AreAdjacent(g, 3, 4));
  ck_assert(AreAdjacent(g, 5, 4));
  ck_assert(AreAdjacent(g, 8, 1));
  ck_assert(AreAdjacent(g, 9, 2));

  // do some removes
  RemoveGraphEdge(g, 3, 10);
  RemoveGraphEdge(g, 4, 2);
  RemoveGraphEdge(g, 9, 2);

  // check adjacencies
  ck_assert(!AreAdjacent(g, 3, 10));
  ck_assert(!AreAdjacent(g, 4, 2));
  ck_assert(!AreAdjacent(g, 9, 2));

  // add some more things
  ck_assert(AddGraphEdge(g, 2, 3, 3) == 0);
  ck_assert(AddGraphEdge(g, 4, 2, 2) == 0);
  ck_assert(AddGraphEdge(g, 5, 6, 3) == 0);

  ck_assert(AreAdjacent(g, 3, 2));
  ck_assert(AreAdjacent(g, 4, 2));
  ck_assert(AreAdjacent(g, 5, 6));

  // okay lets test some neighbors!
  ck_assert(GetNeighbors(g, 3, &out) == 3);
  ck_assert(ContainsNeighbor(out, 3, 2, 3));
  ck_assert(ContainsNeighbor(out, 3, 6, 0));
  ck_assert(ContainsNeighbor(out, 3, 4, 1)); 
  free(out);

  ck_assert(GetNeighbors(g, 4, &out) == 3);
  ck_assert(ContainsNeighbor(out, 3, 2, 2));
  ck_assert(ContainsNeighbor(out, 3, 3, 1));
  ck_assert(ContainsNeighbor(out, 3, 5, 1)); 
  free(out);

  ck_assert(GetNeighbors(g, 7, &out) == 0);
}
END_TEST

Suite *GraphSuite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Graph");

  tc_core = tcase_create("Core");
  tcase_add_checked_fixture(tc_core, setup, teardown);

  tcase_add_test(tc_core, alloc_test);
  tcase_add_test(tc_core, empty_graph_test);
  tcase_add_test(tc_core, single_vertex_test);
  tcase_add_test(tc_core, single_edge_empty_graph_test);
  tcase_add_test(tc_core, single_edge_removal_test);
  tcase_add_test(tc_core, missing_edge_removal_test);
  tcase_add_test(tc_core, missing_edge_and_vertex_removal_test);
  tcase_add_test(tc_core, single_edge_one_vertex_present_test);
  tcase_add_test(tc_core, single_edge_both_vertices_present_test);
  tcase_add_test(tc_core, multiple_edges_populated_graph_test);
  tcase_add_test(tc_core, multiple_edges_from_single_vertex_test);
  tcase_add_test(tc_core, remove_multiple_edges_from_single_vertex_test);
  tcase_add_test(tc_core, get_neighbors_missing_vertex_test);
  tcase_add_test(tc_core, get_neighbors_no_neighbors_test);
  tcase_add_test(tc_core, get_neighbors_single_neighbor_test);
  tcase_add_test(tc_core, get_neighbors_multiple_neighbors_test);
  tcase_add_test(tc_core, pseudo_end_to_end_test);

  suite_add_tcase(s, tc_core);

  return s;
}

// Helper function to determine if the given neighbor with the given weight
// is present in the list specified by out.
bool ContainsNeighbor(Neighbor *out, int capacity, GVertex_t v, int w) {
  Neighbor n;
  int i;

  for (i = 0; i < capacity; i++) {
    n = out[i];
    if (n.v == v && n.weight == w) {
      return true;
    }
  }
  return false;
}
