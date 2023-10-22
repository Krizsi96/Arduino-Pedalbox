#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "SerialInterface.hpp"
#include "TimeInterface.hpp"

class Log {
 public:
  enum kLogType { kInfo, kWarning, kError, kDebug };
  Log(TimeInterface* Time, SerialInterface* Serial);
  ~Log();
  void createLog(kLogType log_type, const char* file, int line,
                 const char* message);

 private:
  TimeInterface* Time_;
  SerialInterface* Serial_;
};

#endif  //_LOG_HPP_
