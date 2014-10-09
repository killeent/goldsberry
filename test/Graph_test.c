// Original Author: Trevor Killeen (2014)
//
// Test Suite for the Graph ADT and adjacency list implementation.

#include <check.h>

#include "./Graph_test.h"
#include "../src/Graph.h"
#include "../src/Graph_priv.h"

// Basic test that Graph Allocation and Free'ing does not crash. This *does
// not* test for memory leaks. 
START_TEST(alloc_test)
{
  Graph g;

  g = AllocateGraph();
  FreeGraph(g);
}
END_TEST

// Tests adding a single edge to the Graph. Checks that 
//
// 1. ContainsVertex returns true
// 2. AreAdjacent reutrns true
START_TEST(single_edge_test)
{
  Graph g;
  int ret;

  g = AllocateGraph();
  ret = AddGraphEdge(g, 1, 2, 0);
  
  // in the off chance we have a memory error
  ck_assert_msg(ret == 0); 

  ck_assert(ContainsVertex(g, 1));
  ck_assert(ContainsVertex(g, 2));
  ck_assert(AreAdjacent(g, 1, 2));
  ck_assert(AreAdjacent(g, 2, 1)); 

  FreeGraph(g);
}
END_TEST

Suite *GraphSuite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Graph");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, alloc_test);
  tcase_add_test(tc_core, single_edge_test);

  suite_add_tcase(s, tc_core);

  return s;
}
