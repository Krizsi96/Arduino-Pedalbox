#ifndef _PEDAL_HPP_
#define _PEDAL_HPP_

#include <stdint.h>

#include "SensorInterface.hpp"

class Pedal {
 public:
  Pedal(SensorInterface* sensor);
  Pedal();
  ~Pedal();
  int32_t readValue();
  void setOffset(int32_t new_offset);
  void set_sensor(SensorInterface* sensor);
  SensorInterface* get_sensor();

 private:
  SensorInterface* sensor_;
};

#endif  //_PEDAL_HPP_
