#ifndef _ARDUINOTIMEINTERFACE_HPP_
#define _ARDUINOTIMEINTERFACE_HPP_

#include <Arduino.h>
#include <TimeLib.h>

#include "TimeInterface.hpp"

class ArduinoTimeInterface : public TimeInterface {
 public:
  ArduinoTimeInterface();
  ~ArduinoTimeInterface() override = default;
  void SetTime(int hour, int minute, int second, int day, int month,
               int year) override;
  void SetTime(uint32_t time) override;
  uint8_t get_hour() override;
  uint8_t get_minute() override;
  uint8_t get_second() override;
  uint16_t get_millisecond() override;
  void update() override;

 private:
  uint32_t const start_time;
  uint16_t millisecond;
};

#endif  //_ARDUINOTIMEINTERFACE_HPP_
