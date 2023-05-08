#ifndef _LOG_H_
#define _LOG_H_

#include <stdint.h>

#ifdef HOST
#include <string>
#endif

#include "TimeLib_interface.hpp"
#include "arduino_communication_interface.hpp"
#include "arduino_time_interface.hpp"

class Log {
 public:
  enum kLogType { kInfo, kWarning, kError, kDebug };

  Log();
  Log(ArduinoTimeInterface* Time);
  Log(ArduinoSerialInterface* Serial);
  Log(TimeLibInterface* TimeLib);
  Log(ArduinoTimeInterface* Time, ArduinoSerialInterface* Serial,
      TimeLibInterface* TimeLib);
  void digitalClockDisplay();
  void updateTime();
  void createLog(kLogType log_type, const char* file, int line,
                 const char* message);

 protected:
 private:
  uint32_t const start_time;
  uint32_t second_counter;
  uint32_t millis_counter;
  uint32_t millisecond;
  bool time_updated;
  ArduinoTimeInterface* Time_;
  TimeLibInterface* TimeLib_;
  ArduinoSerialInterface* Serial_;

  void printDigits(int digits);
};

#endif  //_LOG_H_