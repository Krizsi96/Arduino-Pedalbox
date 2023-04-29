#ifndef _LOG_H_
#define _LOG_H_

#include <Arduino.h>
#include <TimeLib.h>

class Log {
 public:
  Log();
  void digitalClockDisplay();
  void updateTime();

  enum kLogType { kInfo, kWarning, kError, kDebug };

 protected:
 private:
  uint32_t const start_time;
  uint32_t time;
  uint32_t previous_millisecond;
  uint32_t millisecond;

  void printDigits(int digits);
};

#endif  //_LOG_H_