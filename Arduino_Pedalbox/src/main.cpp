#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedal.hpp"
#include "SensorConfig.h"

ArduinoWrapper arduino;
long time = 0;
long previous_time = 0;

LoadCell load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Pedal brake_pedal(&load_cell);

void setup() {
  Serial.begin(9600);
  brake_pedal.setOffset(BRAKE_PEDAL_OFFSET);
}

void loop() {
  time = millis();
  if ((time - previous_time) > 1000) {
    previous_time = time;
    int32_t brake_pedal_reading = brake_pedal.readValue();
    Serial.println(brake_pedal_reading);
  }
}
