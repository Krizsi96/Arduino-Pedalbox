#ifndef _SENSORINTERFACE_HPP_
#define _SENSORINTERFACE_HPP_

#include <Filters.h>
#include <stdint.h>

class SensorInterface {
 public:
  virtual int32_t getReadingValue() = 0;
  virtual void setOffset(int32_t new_offset) = 0;
  virtual int32_t getRawReadingValue() = 0;
  virtual ~SensorInterface() {}
  virtual void setFilter(FILTER_TYPE filter_type, float cut_off_frequency,
                         float initial_value) = 0;
};

#endif  //_SENSORINTERFACE_HPP_
