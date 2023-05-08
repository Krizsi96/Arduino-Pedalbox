#ifndef _ARDUINO_COMMUNICATION_INTERFACE_H_
#define _ARDUINO_COMMUNICATION_INTERFACE_H_

#ifndef HOST
#include <Arduino.h>
#else
#include <gmock/gmock.h>

#include <string>

#include "fake_arduino.hpp"
#endif

class ArduinoSerialInterface {
 public:
  virtual ~ArduinoSerialInterface(){};
  virtual void begin(int baud_rate) { Serial.begin(baud_rate); };
  virtual void print(const char* str) { Serial.print(str); };
  virtual void print(int number) { Serial.print(number); };
#ifdef HOST
  virtual void print(const std::string& str){};
#endif
};

#ifdef HOST
class ArduinoSerialMock : public ArduinoSerialInterface {
 public:
  MOCK_METHOD(void, begin, (int baud_rate), (override));
  MOCK_METHOD(void, print, (const char* str), (override));
  MOCK_METHOD(void, print, (const std::string& str), (override));
  MOCK_METHOD(void, print, (int number), (override));
};
#endif

#endif  //_ARDUINO_COMMUNICATION_INTERFACE_H_