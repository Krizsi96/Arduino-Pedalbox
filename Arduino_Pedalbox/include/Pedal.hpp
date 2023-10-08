#ifndef _PEDAL_HPP_
#define _PEDAL_HPP_

#include <ArxSmartPtr.h>
#include <stdint.h>

#include "SensorInterface.hpp"

class Pedal {
 public:
  Pedal(std::shared_ptr<SensorInterface> sensor);
  Pedal();
  ~Pedal();
  int32_t readValue();
  void setOffset(int32_t new_offset);
  void set_sensor(std::shared_ptr<SensorInterface> sensor);
  std::shared_ptr<SensorInterface> get_sensor();
  int32_t RawReadingValue();

 private:
  std::shared_ptr<SensorInterface> sensor_;
};

#endif  //_PEDAL_HPP_
