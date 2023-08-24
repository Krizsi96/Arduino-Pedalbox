#ifndef _PEDAL_HPP_
#define _PEDAL_HPP_

#include <stdint.h>

#include "SensorInterface.hpp"

class Pedal {
 public:
  int32_t readValue();
  void setOffset(int32_t new_offset);
  Pedal(SensorInterface* sensor);
  ~Pedal();

 private:
  SensorInterface* sensor_;
};

#endif  //_PEDAL_HPP_
