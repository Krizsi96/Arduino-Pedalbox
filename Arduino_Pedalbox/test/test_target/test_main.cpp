#include <Arduino.h>
#include <unity.h>

#include "TimeLib_interface_test.hpp"

// #include "log.h"

#define BUTTON_PIN 5

#ifdef MANUAL_TEST

Log logging;
long time = 0;
long previous_time = 0;
bool button_pressed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  logging.updateTime();

  time = millis();
  if ((time - previous_time) > 1000) {
    previous_time = time;
    logging.createLog(logging.kInfo, __FILE__, __LINE__, "one second passed");
  }

  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (!button_pressed) {
      logging.createLog(logging.kDebug, __FILE__, __LINE__, "button pressed");
      button_pressed = true;
    }
  } else {
    if (button_pressed) {
      logging.createLog(logging.kDebug, __FILE__, __LINE__, "button released");
      button_pressed = false;
    }
  }
}

#else

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  UNITY_BEGIN();
  run_time_lib_interface_test();
  UNITY_END();
}

void loop() { delay(1000); }

#endif  // MANUAL_TEST