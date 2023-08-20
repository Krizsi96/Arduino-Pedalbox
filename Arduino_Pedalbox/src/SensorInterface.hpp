#ifndef _SENSORINTERFACE_HPP_
#define _SENSORINTERFACE_HPP_

#include <stdint.h>

class SensorInterface {
 public:
  virtual int32_t getReadingValue() = 0;
  virtual void updateOffset() = 0;
  virtual ~SensorInterface(){};
};

#endif  //_SENSORINTERFACE_HPP_
