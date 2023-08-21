#include "LoadCell.hpp"

LoadCell::LoadCell(byte serial_clock_pin_init, byte serial_data_pin_init)
    : serial_clock_pin_(serial_clock_pin_init),
      serial_data_pin_(serial_data_pin_init) {}

void LoadCell::begin() {
  load_cell_.begin(serial_data_pin_, serial_clock_pin_);
}

int32_t LoadCell::getReadingValue() {
  int32_t reading = load_cell_.get_value();
  return reading;
}

void LoadCell::updateOffset(int32_t new_offset) {
  int32_t offset_to_substract = new_offset * -1;
  load_cell_.set_offset(offset_to_substract);
}
