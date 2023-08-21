#ifndef _LOADCELL_HPP_
#define _LOADCELL_HPP_

#include <HX711.h>

#include "SensorInterface.hpp"

class LoadCell : public SensorInterface {
 public:
  LoadCell(byte serial_clock_pin_init, byte serial_data_pin_init);
  ~LoadCell() override = default;
  void begin();
  int32_t getReadingValue() override;
  void updateOffset() override;

 private:
  HX711 load_cell_;
  byte serial_clock_pin_;
  byte serial_data_pin_;
};

#endif  //_LOADCELL_HPP_
