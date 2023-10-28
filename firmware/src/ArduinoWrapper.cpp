#include "ArduinoWrapper.hpp"

#include "ArduinoSerialInterface.hpp"
#include "ArduinoTimeInterface.hpp"

ArduinoWrapper::ArduinoWrapper() : Serial(), Time() {}

ArduinoWrapper::~ArduinoWrapper() {}

/*
 * ArduinoSerialInterface
 */

ArduinoSerialInterface::ArduinoSerialInterface() {}

void ArduinoSerialInterface::begin(unsigned long baud_rate) {
  ::Serial.begin(baud_rate);
}

size_t ArduinoSerialInterface::write(const char* string_to_write) {
  return ::Serial.print(string_to_write);
}

/*
 * ArduinoTimeInterface
 */

ArduinoTimeInterface::ArduinoTimeInterface()
    : start_time(1356998400), millisecond(0) {}

void ArduinoTimeInterface::SetTime(int hour, int minute, int second, int day,
                                   int month, int year) {
  setTime(hour, minute, second, day, month, year);
}

void ArduinoTimeInterface::SetTime(uint32_t time) { setTime(time); }

uint8_t ArduinoTimeInterface::get_hour() { return hour(); }

uint8_t ArduinoTimeInterface::get_minute() { return minute(); }

uint8_t ArduinoTimeInterface::get_second() { return second(); }

uint16_t ArduinoTimeInterface::get_millisecond() { return millisecond; }

void ArduinoTimeInterface::update() {
  uint32_t current_millis = millis();
  uint32_t current_second = current_millis / 1000;
  millisecond = current_millis % 1000;
  SetTime(start_time + current_second);
}