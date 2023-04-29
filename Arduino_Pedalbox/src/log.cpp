#include "log.h"

Log::Log()
    : start_time(1356998400), counter(0), millisecond(0), time(start_time) {
  setTime(start_time);
}

void Log::printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and
  // leading 0
  Serial.print(":");
  if (digits < 10) Serial.print('0');
  Serial.print(digits);
}

void Log::digitalClockDisplay(uint8_t const refresh_period) {
  if (counter % refresh_period == 0) {  // in milliseconds
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
    Serial.println();
  }
}

void Log::updateTime() {
  if (counter % 1000 == 0) {  // every second
    time = time + 1;
  }
  setTime(time);
  uint32_t seconds = (counter / 1000) * 1000;
  millisecond = (counter - seconds);
  counter = millis();
}