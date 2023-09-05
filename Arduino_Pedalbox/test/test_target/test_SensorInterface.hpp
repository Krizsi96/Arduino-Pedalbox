#include <unity.h>

#include "LoadCell.hpp"
#include "Potmeter.cpp"
#include "Potmeter.hpp"

#define TEST_POTMETER_PIN A0

void read_potmeter_value(void) {
  // Given
  Potmeter test_potmeter(TEST_POTMETER_PIN);

  // When
  int32_t actual_reading = test_potmeter.getReadingValue();

  // Then
  int32_t expected_reading = analogRead(TEST_POTMETER_PIN);
  TEST_ASSERT_EQUAL(expected_reading, actual_reading);
}

void set_offset_for_potmeter(void) {
  // Given
  Potmeter test_potmeter(TEST_POTMETER_PIN);
  int32_t offset = 100;

  // When
  test_potmeter.setOffset(offset);

  // Then
  int32_t actual_reading = test_potmeter.getReadingValue();
  int32_t expected_reading = analogRead(TEST_POTMETER_PIN) + offset;
  TEST_ASSERT_EQUAL(expected_reading, actual_reading);
}