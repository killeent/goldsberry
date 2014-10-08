// Original Author: Trevor Killeen (2014)
//
// Test runner for Graph and Graph algorithms. 

#include <check.h>

#include "test/Graph_test.h"

int main() {
  Suite *s;
  SRunner *runner;
  int failures;

  s = GraphSuite();
  runner = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  failures = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failures;
}
