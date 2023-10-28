#ifndef _ARDUINOWRAPPER_HPP_
#define _ARDUINOWRAPPER_HPP_

#include <Arduino.h>

#include "ArduinoSerialInterface.hpp"
#include "ArduinoTimeInterface.hpp"

class ArduinoWrapper {
 public:
  ArduinoSerialInterface Serial;
  ArduinoTimeInterface Time;
  ArduinoWrapper();
  ~ArduinoWrapper();
};

#endif  //_ARDUINOWRAPPER_HPP_
