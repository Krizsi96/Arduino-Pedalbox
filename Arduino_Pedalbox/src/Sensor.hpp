#ifndef _SENSOR_HPP_
#define _SENSOR_HPP_

#include <stdint.h>

class Sensor {
 public:
  virtual int32_t getRawValue() = 0;
  virtual void applyFilter() = 0;
  virtual void applyOffset() = 0;
  virtual void updateOffset() = 0;
  virtual void updateFilterParameter() = 0;
  virtual ~Sensor(){};
};

#endif  //_SENSOR_HPP_
