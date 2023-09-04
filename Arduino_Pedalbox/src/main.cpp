#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedal.hpp"
#include "Potmeter.hpp"
#include "SensorConfig.h"

ArduinoWrapper arduino;
long time = 0;
long previous_time = 0;

LoadCell load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Potmeter potmeter(THROTTLE_PEDAL_PIN);
Pedal brake_pedal(&load_cell);
Pedal throttle_pedal(&potmeter);

void setup() {
  Serial.begin(9600);
  brake_pedal.setOffset(BRAKE_PEDAL_OFFSET);
  throttle_pedal.setOffset(THROTTLE_PEDAL_OFFSET);
}

void loop() {
  time = millis();
  if ((time - previous_time) > 1000) {
    previous_time = time;
    int32_t brake_pedal_reading = brake_pedal.readValue();
    int32_t throttle_pedal_reading = throttle_pedal.readValue();
    Serial.print("Brake:\t");
    Serial.print(brake_pedal_reading);
    Serial.print("\t Throttle:\t");
    Serial.println(throttle_pedal_reading);
  }
}
