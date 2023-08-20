#ifndef _PEDAL_HPP_
#define _PEDAL_HPP_

#include <stdint.h>

#include "Sensor.hpp"

class Pedal {
 public:
  int32_t readValue();
  void setOffset();
  void setFilter();
  Pedal();
  ~Pedal();
};

#endif  //_PEDAL_HPP_
