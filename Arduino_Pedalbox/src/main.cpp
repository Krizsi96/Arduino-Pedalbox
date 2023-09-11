#include <Filters.h>
#include <arduino-timer.h>

#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedal.hpp"
#include "Potmeter.hpp"
#include "SensorConfig.h"

#define FILTER_FREQUENCY 10

ArduinoWrapper arduino;

auto timer = timer_create_default();

LoadCell brake_load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Potmeter throttle_potmeter(THROTTLE_PEDAL_PIN);
Potmeter clutch_potmeter(CLUTCH_PEDAL_PIN);

Pedal brake_pedal(&brake_load_cell);
Pedal throttle_pedal(&throttle_potmeter);
Pedal clutch_pedal(&clutch_potmeter);

FilterOnePole brake_filter_lowpass(LOWPASS, FILTER_FREQUENCY);

bool showPedalReadings(void *);

void setup() {
  Serial.begin(9600);
  brake_pedal.setOffset(BRAKE_PEDAL_OFFSET);
  throttle_pedal.setOffset(THROTTLE_PEDAL_OFFSET);
  clutch_pedal.setOffset(CLUTCH_PEDAL_OFFSET);
  timer.every(1, showPedalReadings);
}

void loop() { timer.tick(); }

bool showPedalReadings(void *) {
  int32_t brake_pedal_reading = brake_pedal.readValue();
  int32_t throttle_pedal_reading = throttle_pedal.readValue();
  int32_t clutch_pedal_reading = clutch_pedal.readValue();

  brake_filter_lowpass.input(brake_pedal_reading);

  Serial.print(">brake:");
  Serial.println(brake_pedal_reading);
  Serial.print(">brake_filter:");
  Serial.println(brake_filter_lowpass.output());
  Serial.print(">throttle:");
  Serial.println(throttle_pedal_reading);
  Serial.print(">clutch:");
  Serial.println(clutch_pedal_reading);
  return true;
}
