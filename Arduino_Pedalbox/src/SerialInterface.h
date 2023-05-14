#ifndef _SERIALINTERFACE_H_
#define _SERIALINTERFACE_H_

#include <stdint.h>

#ifdef HOST
#include <cstddef>
#endif

class SerialInterface {
 public:
  virtual ~SerialInterface(){};
  virtual void begin(unsigned long baud_rate) = 0;
  virtual size_t write(const char* string_to_write) = 0;

 protected:
 private:
};

#endif  //_SERIALINTERFACE_H_