#ifndef _ARDUINO_TIME_INTERFACE_H_
#define _ARDUINO_TIME_INTERFACE_H_

#ifndef HOST
#include <Arduino.h>
#else
#include <gmock/gmock.h>

#include "fake_arduino.hpp"
#endif

class ArduinoTimeInterface {
 public:
  ArduinoTimeInterface(){};
  virtual ~ArduinoTimeInterface(){};
  virtual void DelayInMilliseconds(int milliseconds) { delay(milliseconds); };
  virtual void DelayInMicroseconds(int microseconds) {
    delayMicroseconds(microseconds);
  };
  virtual unsigned long InMillis() { return millis(); };
  virtual unsigned long InMicros() { return micros(); };
};
#ifdef HOST
class ArduinoTimeMock : public ArduinoTimeInterface {
 public:
  MOCK_METHOD(void, DelayInMilliseconds, (int milliseconds), (override));
  MOCK_METHOD(void, DelayInMicroseconds, (int microseconds), (override));
  MOCK_METHOD(unsigned long, InMillis, (), (override));
  MOCK_METHOD(unsigned long, InMicros, (), (override));
};
#endif

#endif  //_ARDUINO_TIME_INTERFACE_H_