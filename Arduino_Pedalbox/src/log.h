#ifndef _LOG_H_
#define _LOG_H_

#include <Arduino.h>
#include <TimeLib.h>

class Log {
 public:
  enum kLogType { kInfo, kWarning, kError, kDebug };

  Log();
  void digitalClockDisplay();
  void updateTime();
  void createLog(kLogType log_type, const char* file, int line,
                 const char* message);

 protected:
 private:
  uint32_t const start_time;
  uint32_t time;
  uint32_t counter;
  uint32_t millisecond;

  void printDigits(int digits);
};

#endif  //_LOG_H_