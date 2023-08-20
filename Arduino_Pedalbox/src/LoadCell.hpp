#ifndef _LOADCELL_HPP_
#define _LOADCELL_HPP_

#include <HX711.h>

#include "Sensor.hpp"

class LoadCell : public Sensor {
 public:
  int32_t getRawValue();
  void applyFilter();
  void applyOffset();
  void updateFilterParameter();
  LoadCell();
  ~LoadCell();
};

#endif  //_LOADCELL_HPP_
