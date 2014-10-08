// Original Author: Trevor Killeen (2014)
//
// Test Suite for the Graph ADT and adjacency list implementation.

#include <check.h>

#include "./Graph_test.h"
#include "../src/Graph.h"
#include "../src/Graph_priv.h"

START_TEST(basic_test)
{
  Graph g;

  g = AllocateGraph();
  FreeGraph(g);
}
END_TEST

Suite *GraphSuite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Graph");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, basic_test);

  suite_add_tcase(s, tc_core);

  return s;
}
