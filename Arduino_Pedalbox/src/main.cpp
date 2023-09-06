#include <arduino-timer.h>

#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedal.hpp"
#include "Potmeter.hpp"
#include "SensorConfig.h"

ArduinoWrapper arduino;

auto timer = timer_create_default();

LoadCell brake_load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Potmeter throttle_potmeter(THROTTLE_PEDAL_PIN);
Potmeter clutch_potmeter(CLUTCH_PEDAL_PIN);

Pedal brake_pedal(&brake_load_cell);
Pedal throttle_pedal(&throttle_potmeter);
Pedal clutch_pedal(&clutch_potmeter);

bool showPedalReadings(void *);

void setup() {
  Serial.begin(9600);
  brake_pedal.setOffset(BRAKE_PEDAL_OFFSET);
  throttle_pedal.setOffset(THROTTLE_PEDAL_OFFSET);
  clutch_pedal.setOffset(CLUTCH_PEDAL_OFFSET);
  timer.every(250, showPedalReadings);
}

void loop() { timer.tick(); }

bool showPedalReadings(void *) {
  int32_t brake_pedal_reading = brake_pedal.readValue();
  int32_t throttle_pedal_reading = throttle_pedal.readValue();
  int32_t clutch_pedal_reading = clutch_pedal.readValue();
  Serial.print("Brake:\t");
  Serial.print(brake_pedal_reading);
  Serial.print("\t Throttle:\t");
  Serial.print(throttle_pedal_reading);
  Serial.print("\t Clutch:\t");
  Serial.println(clutch_pedal_reading);
  return true;
}
