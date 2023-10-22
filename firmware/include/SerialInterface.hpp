#ifndef _SERIALINTERFACE_HPP_
#define _SERIALINTERFACE_HPP_

#include <stdint.h>

#ifdef HOST
#include <cstddef>
#endif

class SerialInterface {
 public:
  virtual ~SerialInterface() {}
  virtual void begin(unsigned long baud_rate) = 0;
  virtual size_t write(const char* string_to_write) = 0;
};

#endif  //_SERIALINTERFACE_HPP_
