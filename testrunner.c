// Original Author: Trevor Killeen (2014)
//
// Test runner for Graph and Graph algorithms. 

#include <stdlib.h>
#include <check.h>

#include "test/Graph_test.h"

int main() {
  Suite *s;
  SRunner *runner;
  int failures;

  s = GraphSuite();
  runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  failures = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failures;
}
