#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "SensorConfig.h"

ArduinoWrapper arduino;
long time = 0;
long previous_time = 0;

LoadCell load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);

void setup() {
  Serial.begin(9600);
  load_cell.setOffset(BRAKE_PEDAL_OFFSET);
}

void loop() {
  time = millis();
  if ((time - previous_time) > 1000) {
    previous_time = time;
    int32_t load_cell_reading = load_cell.getReadingValue();
    Serial.println(load_cell_reading);
  }
}