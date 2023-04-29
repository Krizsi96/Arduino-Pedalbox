#include "log.h"

Log::Log()
    : start_time(1357041600),
      previous_millisecond(0),
      millisecond(0),
      time(start_time) {
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
  // digital clock display of the time

  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(".");
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void Log::updateTime() {
  millisecond = millis();
  setTime(time);

  if (millisecond % 100 == 0) {
    Serial.print("\n");
    Serial.print("time: ");
    Serial.print(millisecond);
    Serial.print(" milliseconds\n");

    // digital clock display of the time
    digitalClockDisplay();

    Serial.print("prev_millisecond: ");
    Serial.print(previous_millisecond);
    Serial.print(" milliseconds\n");
  }

  uint32_t elapsed_milliseconds = millisecond - previous_millisecond;
  if (elapsed_milliseconds % 1000 == 0) {
    time = time + 1;
    previous_millisecond = millisecond;
  }
}