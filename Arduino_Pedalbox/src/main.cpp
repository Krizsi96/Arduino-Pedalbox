#include <Arduino.h>

#include "log.h"

Log logging;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  logging.updateTime();
}