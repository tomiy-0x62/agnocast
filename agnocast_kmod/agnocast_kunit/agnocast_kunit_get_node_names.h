#pragma once
#include <kunit/test.h>

#define TEST_CASES_GET_NODE_NAMES                   \
  KUNIT_CASE(test_case_get_node_names)

void test_case_get_node_names(struct kunit * test);
