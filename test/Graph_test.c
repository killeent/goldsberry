// Original Author: Trevor Killeen (2014)
//
// Test Suite for the Graph ADT and adjacency list implementation.

#include <check.h>

#include "./Graph_test.h"
#include "../src/Graph.h"
#include "../src/Graph_priv.h"

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

  ck_assert(ContainsVertex(g, 0) == false);
  ck_assert(AreAdjacent(g, 0, 1) == false);
  ck_assert(GetNeighbors(g, 0, &out) == -1);
  RemoveGraphEdge(g, 0, 1);
}
END_TEST

// Tests adding a single vertex to the Graph.
START_TEST(single_vertex_test) {
}
END_TEST

// Tests adding a single edge to the an empty Graph. Checks that 
//
// 1. ContainsVertex returns true
// 2. AreAdjacent returns true
START_TEST(single_edge_empty_graph_test)
{
  // in the off chance we have a memory error
  ck_assert(AddGraphEdge(g, 1, 2, 0) == 0); 

  ck_assert(ContainsVertex(g, 1));
  ck_assert(ContainsVertex(g, 2));
  ck_assert(AreAdjacent(g, 1, 2));
  ck_assert(AreAdjacent(g, 2, 1)); 
}
END_TEST

// Tests removing a single edge from the Graph.

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

  suite_add_tcase(s, tc_core);

  return s;
}
