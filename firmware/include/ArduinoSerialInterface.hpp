#ifndef _ARDUINOSERIALINTERFACE_HPP_
#define _ARDUINOSERIALINTERFACE_HPP_

#include <Arduino.h>

#include "SerialInterface.hpp"

class ArduinoSerialInterface : public SerialInterface {
 public:
  ArduinoSerialInterface();
  ~ArduinoSerialInterface() override = default;
  void begin(unsigned long baud_rate) override;
  size_t write(const char* string_to_write) override;
};

#endif  //_ARDUINOSERIALINTERFACE_HPP_
