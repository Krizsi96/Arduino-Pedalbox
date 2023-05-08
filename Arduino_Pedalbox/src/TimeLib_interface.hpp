#ifndef _TIMELIB_INTERFACE_H_
#define _TIMELIB_INTERFACE_H_

#ifndef HOST
#include <Arduino.h>
#include <TimeLib.h>
#else
#include <gmock/gmock.h>
#include <stdint.h>

#include <cstring>
// fake external dependencies
extern void setTime(int hour, int minute, int second, int day, int month,
                    int year);
extern void setTime(uint32_t time);
extern int hour();
extern int minute();
extern int second();
#endif

class TimeLibInterface {
 public:
  TimeLibInterface(){};
  virtual ~TimeLibInterface(){};
  virtual void SetTime(int hour, int minute, int second, int day, int month,
                       int year) {
    setTime(hour, minute, second, day, month, year);
  };
  virtual void SetTime(uint32_t time) { setTime(time); };
  virtual int get_hour() { return hour(); };
  virtual int get_minute() { return minute(); };
  virtual int get_second() { return second(); };
};
#ifdef HOST
class TimeLibMock : public TimeLibInterface {
 public:
  MOCK_METHOD(void, SetTime,
              (int hour, int minute, int second, int day, int month, int year),
              (override));
  MOCK_METHOD(void, SetTime, (uint32_t time), (override));
  MOCK_METHOD(int, get_hour, (), (override));
  MOCK_METHOD(int, get_minute, (), (override));
  MOCK_METHOD(int, get_second, (), (override));
};
#endif

#endif  //_TIMELIB_INTERFACE_H_
