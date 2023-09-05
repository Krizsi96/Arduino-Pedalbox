#include <unity.h>

#include <ArduinoWrapper.cpp>
#include <ArduinoWrapper.hpp>

void test_if_hour_is_set_correctly(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(1, 0, 0, 1, 1, 1970);
  TEST_ASSERT_EQUAL(1, arduino.Time.get_hour());
}

void test_if_minute_is_set_correctly(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(0, 1, 0, 1, 1, 1970);
  TEST_ASSERT_EQUAL(1, arduino.Time.get_minute());
}

void test_if_second_is_set_correctly(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(0, 0, 1, 1, 1, 1970);
  TEST_ASSERT_EQUAL(1, arduino.Time.get_second());
}

void test_if_hour_is_set_correctly_with_unix_time(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(1356998400);
  TEST_ASSERT_EQUAL(0, arduino.Time.get_hour());
}

void test_if_minute_is_set_correctly_with_unix_time(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(1356998400);
  TEST_ASSERT_EQUAL(0, arduino.Time.get_minute());
}

void test_if_second_is_set_correctly_with_unix_time(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(1356998400);
  TEST_ASSERT_EQUAL(0, arduino.Time.get_second());
}

void test_if_time_is_updated(void) {
  ArduinoWrapper arduino;
  arduino.Time.SetTime(1356998400);
  uint16_t previous_millisecond = arduino.Time.get_millisecond();
  for (int i = 0; i < 1000; i++) {
  }
  arduino.Time.update();
  TEST_ASSERT_NOT_EQUAL(previous_millisecond, arduino.Time.get_millisecond());
}
