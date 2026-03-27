#pragma once
#include <kunit/test.h>

#define TEST_CASES_ADD_REMOVE_PUBLISHER_SUBSCRIBER         \
  KUNIT_CASE(test_case_add_publisher_subscriber_too_many), \
    KUNIT_CASE(test_case_add_remove_publisher_subscriber)

void test_case_add_publisher_subscriber_too_many(struct kunit * test);
void test_case_add_remove_publisher_subscriber(struct kunit * test);
