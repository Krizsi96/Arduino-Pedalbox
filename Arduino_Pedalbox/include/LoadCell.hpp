#ifndef _LOADCELL_HPP_
#define _LOADCELL_HPP_

#include <Filters.h>
#include <HX711.h>

#include "SensorInterface.hpp"

class LoadCell : public SensorInterface {
 public:
  LoadCell(byte serial_clock_pin_init, byte serial_data_pin_init);
  ~LoadCell() override = default;
  int32_t getReadingValue() override;
  void setOffset(int32_t new_offset) override;
  void setFilter(FILTER_TYPE filter_type, float cut_off_frequency,
                 float initial_value);
  int32_t getRawReadingValue();

 private:
  HX711 load_cell_;
  FilterOnePole filter_;
  int32_t applyFilterTo(int32_t raw_reading);
};

#endif  //_LOADCELL_HPP_
