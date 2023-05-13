#include <Arduino.h>
#include <unity.h>

#include <TimeLib_interface.hpp>

void run_time_lib_interface_test(void) {
  RUN_TEST(test_if_hour_is_set_correctly);
  RUN_TEST(test_if_minute_is_set_correctly);
  RUN_TEST(test_if_second_is_set_correctly);
  RUN_TEST(test_if_hour_is_set_correctly_with_unix_time);
  RUN_TEST(test_if_minute_is_set_correctly_with_unix_time);
  RUN_TEST(test_if_second_is_set_correctly_with_unix_time);
}

void test_if_hour_is_set_correctly(void) {
  TimeLibInterface time_lib;
  time_lib.SetTime(0, 0, 0, 1, 1, 2020);
  TEST_ASSERT_EQUAL(0, time_lib.get_hour());
}

void test_if_minute_is_set_correctly(void) {
  TimeLibInterface time_lib;
  time_lib.SetTime(0, 0, 0, 1, 1, 2020);
  TEST_ASSERT_EQUAL(0, time_lib.get_minute());
}

void test_if_second_is_set_correctly(void) {
  TimeLibInterface time_lib;
  time_lib.SetTime(0, 0, 0, 1, 1, 2020);
  TEST_ASSERT_EQUAL(0, time_lib.get_second());
}

void test_if_hour_is_set_correctly_with_unix_time(void) {
  TimeLibInterface time_lib;
  time_lib.SetTime(1577836800);
  TEST_ASSERT_EQUAL(0, time_lib.get_hour());
}

void test_if_minute_is_set_correctly_with_unix_time(void) {
  TimeLibInterface time_lib;
  time_lib.SetTime(1577836800);
  TEST_ASSERT_EQUAL(0, time_lib.get_minute());
}

void test_if_second_is_set_correctly_with_unix_time(void) {
  TimeLibInterface time_lib;
  time_lib.SetTime(1577836800);
  TEST_ASSERT_EQUAL(0, time_lib.get_second());
}