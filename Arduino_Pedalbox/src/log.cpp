#include "log.h"

Log::Log()
    : start_time(1357041600),
      counter(0),
      counter_previous(0),
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
  counter = millis();
  setTime(time);

  if (counter % 100 == 0) {
    Serial.print("\n");
    Serial.print("counter: ");
    Serial.print(counter);
    Serial.print(" milliseconds\n");

    // digital clock display of the time
    digitalClockDisplay();
  }

  if (counter % 1000 == 0) {
    time = time + 1;
  }
}