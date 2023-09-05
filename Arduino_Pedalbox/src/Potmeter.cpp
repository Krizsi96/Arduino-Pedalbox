#include "Potmeter.hpp"

#include <Arduino.h>

Potmeter::Potmeter(uint8_t analog_pin_init)
    : analog_pin_(analog_pin_init), offset_(0) {}

int32_t Potmeter::getReadingValue() {
  return analogRead(analog_pin_) + offset_;
}

void Potmeter::setOffset(int32_t new_offset) { offset_ = new_offset; }
