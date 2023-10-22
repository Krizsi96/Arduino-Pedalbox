#include "Potmeter.hpp"

#include <Arduino.h>

Potmeter::Potmeter(uint8_t analog_pin_init)
    : analog_pin_(analog_pin_init), offset_(0) {}

int32_t Potmeter::getReadingValue() {
  int32_t raw_reading = getRawReadingValue();
  int32_t reading = applyFilterTo(raw_reading);
  return reading;
}

void Potmeter::setOffset(int32_t new_offset) { offset_ = new_offset; }

void Potmeter::setFilter(FILTER_TYPE filter_type, float cut_off_frequency,
                         float initial_value) {
  filter_.setFilter(filter_type, cut_off_frequency, initial_value);
}

int32_t Potmeter::applyFilterTo(int32_t raw_reading) {
  int32_t filtered_reading = filter_.input(raw_reading);
  return filtered_reading;
}

int32_t Potmeter::getRawReadingValue() {
  return analogRead(analog_pin_) + offset_;
}
