#ifndef _LOG_NEW_H
#define _LOG_NEW_H

#include <stdio.h>
#include <string.h>

#include "SerialInterface.h"
#include "TimeInterface.h"

class Log {
 public:
  enum kLogType { kInfo, kWarning, kError, kDebug };
  Log(SerialInterface* Serial, TimeInterface* Time);
  ~Log();
  void updateTime();
  void createLog(kLogType log_type, const char* file, int line,
                 const char* message);

 private:
  SerialInterface* Serial_;
  TimeInterface* Time_;
};

#endif  //_LOG_NEW_H