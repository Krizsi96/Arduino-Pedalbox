#include "ArduinoWrapper.h"

ArduinoWrapper::ArduinoWrapper() : Serial(), Time() {}

ArduinoWrapper::~ArduinoWrapper() {}

/*
 * ArduinoSerialInterface
 */

ArduinoWrapper::ArduinoSerialInterface::ArduinoSerialInterface() {}

void ArduinoWrapper::ArduinoSerialInterface::begin(unsigned long baud_rate) {
  ::Serial.begin(baud_rate);
}

size_t ArduinoWrapper::ArduinoSerialInterface::write(
    const char* string_to_write) {
  return ::Serial.print(string_to_write);
}

/*
 * ArduinoTimeInterface
 */

ArduinoWrapper::ArduinoTimeInterface::ArduinoTimeInterface()
    : start_time(1356998400), millisecond(0) {}

void ArduinoWrapper::ArduinoTimeInterface::SetTime(int hour, int minute,
                                                   int second, int day,
                                                   int month, int year) {
  setTime(hour, minute, second, day, month, year);
}

void ArduinoWrapper::ArduinoTimeInterface::SetTime(uint32_t time) {
  setTime(time);
}

uint8_t ArduinoWrapper::ArduinoTimeInterface::get_hour() { return hour(); }

uint8_t ArduinoWrapper::ArduinoTimeInterface::get_minute() { return minute(); }

uint8_t ArduinoWrapper::ArduinoTimeInterface::get_second() { return second(); }

uint16_t ArduinoWrapper::ArduinoTimeInterface::get_millisecond() {
  return millisecond;
}

void ArduinoWrapper::ArduinoTimeInterface::update() {
  uint32_t current_millis = millis();
  uint32_t current_second = current_millis / 1000;
  millisecond = current_millis % 1000;
  SetTime(start_time + current_second);
}