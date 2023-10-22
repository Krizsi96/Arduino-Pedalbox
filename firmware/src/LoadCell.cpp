#include "LoadCell.hpp"

LoadCell::LoadCell(byte serial_clock_pin_init, byte serial_data_pin_init) {
  load_cell_.begin(serial_data_pin_init, serial_clock_pin_init);
}

int32_t LoadCell::getReadingValue() {
  int32_t raw_reading = getRawReadingValue();
  int32_t reading = applyFilterTo(raw_reading);
  return reading;
}

void LoadCell::setOffset(int32_t new_offset) {
  int32_t offset_to_substract = new_offset * -1;
  load_cell_.set_offset(offset_to_substract);
}

void LoadCell::setFilter(FILTER_TYPE filter_type, float cut_off_frequency,
                         float initial_value) {
  filter_.setFilter(filter_type, cut_off_frequency, initial_value);
}

int32_t LoadCell::applyFilterTo(int32_t raw_reading) {
  int32_t filtered_reading = filter_.input(raw_reading);
  return filtered_reading;
}

int32_t LoadCell::getRawReadingValue() {
  int32_t reading = load_cell_.get_value();
  return reading;
}
