#include "log.h"

Log::Log()
    : start_time(1356998400),
      counter(0),
      millisecond(0),
      time(start_time),
      time_updated(false) {
  setTime(start_time);
}

void Log::printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and
  // leading 0
  Serial.print(":");
  if (digits < 10) Serial.print('0');
  Serial.print(digits);
}

void Log::digitalClockDisplay() {
  // display counter
  Serial.print("\n");
  Serial.print("counter: ");
  Serial.print(counter);
  Serial.print(" milliseconds\n");

  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(".");
  if (millisecond < 10) {
    Serial.print("00");
  } else if ((10 <= millisecond) && (millisecond < 100)) {
    Serial.print("0");
  }
  Serial.print(millisecond);
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
}

void Log::updateTime() {
  if (counter % 1000 == 0) {  // every second
    if (!time_updated) {
      time++;
      time_updated = true;
    }
  } else {
    time_updated = false;
  }
  setTime(time);
  uint32_t seconds = (counter / 1000) * 1000;
  millisecond = (counter - seconds);
  counter = millis();
}

void Log::createLog(kLogType log_type, const char *file, int line,
                    const char *message) {
  char log_type_str[10];

  digitalClockDisplay();
  Serial.print(" ");
  switch (log_type) {
    case kInfo:
      strcpy(log_type_str, "INFO");
      break;
    case kWarning:
      strcpy(log_type_str, "WARNING");
      break;
    case kError:
      strcpy(log_type_str, "ERROR");
      break;
    case kDebug:
      strcpy(log_type_str, "DEBUG");
      break;
    default:
      strcpy(log_type_str, "UNKNOWN");
      break;
  }
  Serial.print(log_type_str);
  Serial.print(" ");
  Serial.print(file);
  Serial.print(":");
  Serial.print(line);
  Serial.print(": ");
  Serial.print(message);
  Serial.print(" ");
  Serial.print(time);
  Serial.print("\n");
}