#include <unity.h>

#include "LoadCell.cpp"
#include "LoadCell.hpp"
#include "Potmeter.cpp"
#include "Potmeter.hpp"
#include "test_configuration.h"

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

void read_load_cell_value(void) {
  // Given
  LoadCell test_load_cell(LOAD_CELL_CLOCK_PIN, LOAD_CELL_DATA_PIN);

  // When
  int32_t actual_reading = test_load_cell.getReadingValue();

  // Then
  int32_t expected_reading =
      0;  // LOAD_CELL_DATA_PIN should be connected to ground
  TEST_ASSERT_EQUAL(expected_reading, actual_reading);
}

void set_offset_for_load_cell(void) {
  // Given
  LoadCell test_load_cell(LOAD_CELL_CLOCK_PIN, LOAD_CELL_DATA_PIN);
  int32_t offset = 100;

  // When
  test_load_cell.setOffset(offset);

  // Then
  int32_t actual_reading = test_load_cell.getReadingValue();
  int32_t expected_reading = offset;
  TEST_ASSERT_EQUAL(expected_reading, actual_reading);
}
