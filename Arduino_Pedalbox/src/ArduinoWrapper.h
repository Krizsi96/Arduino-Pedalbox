#ifndef _TARGETWRAPPER_H_
#define _TARGETWRAPPER_H_

#include <Arduino.h>
#include <TimeLib.h>

#include "SerialInterface.h"
#include "TimeInterface.h"

class ArduinoWrapper {
 public:
  ArduinoWrapper();
  ~ArduinoWrapper();

  class ArduinoSerialInterface : public SerialInterface {
   public:
    ArduinoSerialInterface();
    ~ArduinoSerialInterface() override = default;
    void begin(unsigned long baud_rate) override;
    size_t write(const char* string_to_write) override;
  } Serial;

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
  } Time;
};

#endif  //_TARGETWRAPPER_H_