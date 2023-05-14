#include <ArduinoWrapper.h>
#include <unity.h>

#include "ArduinoWrapper_test.hpp"

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  UNITY_BEGIN();
  run_arduino_wrapper_test();
  UNITY_END();
}

void loop() { delay(1000); }