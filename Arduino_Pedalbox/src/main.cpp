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
int32_t previous_time = 0;
int32_t current_time = 0;

LoadCell brake_load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Potmeter throttle_potmeter(THROTTLE_PEDAL_PIN);
Potmeter clutch_potmeter(CLUTCH_PEDAL_PIN);

Pedal brake_pedal(&brake_load_cell);
Pedal throttle_pedal(&throttle_potmeter);
Pedal clutch_pedal(&clutch_potmeter);

bool showPedalReadings(void *);
void tick();
int32_t tack();

void setup() {
  Serial.begin(9600);

  brake_pedal.setOffset(BRAKE_PEDAL_OFFSET);
  throttle_pedal.setOffset(THROTTLE_PEDAL_OFFSET);
  clutch_pedal.setOffset(CLUTCH_PEDAL_OFFSET);

  brake_load_cell.setFilter(LOWPASS, FILTER_FREQUENCY, 0);
  throttle_potmeter.setFilter(LOWPASS, FILTER_FREQUENCY, 0);
  clutch_potmeter.setFilter(LOWPASS, FILTER_FREQUENCY, 0);

  timer.every(10, showPedalReadings);
}

void loop() { timer.tick(); }

bool showPedalReadings(void *) {
  tick();

  Serial.print(">brake_raw:");
  Serial.println(brake_load_cell.getRawReadingValue());
  Serial.print(">brake_filter:");
  Serial.println(brake_pedal.readValue());

  Serial.print(">throttle:");
  Serial.println(throttle_potmeter.getRawReadingValue());
  Serial.print(">throttle_filter:");
  Serial.println(throttle_pedal.readValue());

  Serial.print(">clutch:");
  Serial.println(clutch_potmeter.getRawReadingValue());
  Serial.print(">clutch_filter:");
  Serial.println(clutch_pedal.readValue());

  Serial.print("cycle time: ");
  Serial.println(tack());

  return true;
}

void tick() { previous_time = micros(); }

int32_t tack() {
  current_time = micros();
  return current_time - previous_time;
}
