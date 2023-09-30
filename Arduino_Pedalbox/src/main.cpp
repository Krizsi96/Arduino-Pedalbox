#include <Joystick.h>
#include <arduino-timer.h>

#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedal.hpp"
#include "Potmeter.hpp"
#include "SensorConfig.h"

ArduinoWrapper arduino;

auto timer = timer_create_default();
int32_t previous_time = 0;
int32_t current_time = 0;
int32_t cycle_time = 0;

LoadCell brake_load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Potmeter throttle_potmeter(THROTTLE_PEDAL_PIN);
Potmeter clutch_potmeter(CLUTCH_PEDAL_PIN);

Pedal brake_pedal(&brake_load_cell);
Pedal throttle_pedal(&throttle_potmeter);
Pedal clutch_pedal(&clutch_potmeter);

struct Pedalbox {
  Joystick_ HIDcontroller;
  int32_t brake;
  int32_t throttle;
  int32_t clutch;
};

Pedalbox pedalbox;

bool showPedalReadings(void *);
bool updateGameController(void *);
void tick();
int32_t tack();

void setup() {
  Serial.begin(9600);
  pedalbox.HIDcontroller.begin();

  brake_pedal.setOffset(BRAKE_PEDAL_OFFSET);
  throttle_pedal.setOffset(THROTTLE_PEDAL_OFFSET);
  clutch_pedal.setOffset(CLUTCH_PEDAL_OFFSET);

  brake_load_cell.setFilter(BRAKE_PEDAL_FILTER_TYPE,
                            BRAKE_PEDAL_FILTER_FREQUENCY,
                            BRAKE_PEDAL_INITIAL_VALUE);
  throttle_potmeter.setFilter(THROTTLE_PEDAL_FILTER_TYPE,
                              THROTTLE_PEDAL_FILTER_FREQUENCY,
                              THROTTLE_PEDAL_INITIAL_VALUE);
  clutch_potmeter.setFilter(CLUTCH_PEDAL_FILTER_TYPE,
                            CLUTCH_PEDAL_FILTER_FREQUENCY,
                            CLUTCH_PEDAL_INITIAL_VALUE);

  pedalbox.HIDcontroller.setRxAxisRange(0, 1023);
  pedalbox.HIDcontroller.setRyAxisRange(0, 30000);
  pedalbox.HIDcontroller.setRzAxisRange(0, 1023);

  timer.every(50, showPedalReadings);
  timer.every(50, updateGameController);
}

void loop() {
  timer.tick();

  tick();
  pedalbox.brake = brake_pedal.readValue();
  pedalbox.throttle = throttle_pedal.readValue();
  pedalbox.clutch = clutch_pedal.readValue();
}

bool showPedalReadings(void *) {
  Serial.print(">brake_filtered:");
  Serial.println(pedalbox.brake);

  Serial.print(">throttle_filtered:");
  Serial.println(pedalbox.throttle);

  Serial.print(">clutch_filtered:");
  Serial.println(pedalbox.clutch);

  Serial.print("cycle time: ");
  Serial.println(cycle_time);

  return true;
}

bool updateGameController(void *) {
  pedalbox.HIDcontroller.setRxAxis(pedalbox.throttle);
  pedalbox.HIDcontroller.setRyAxis(pedalbox.brake);
  pedalbox.HIDcontroller.setRzAxis(pedalbox.clutch);
  cycle_time = tack();
  return true;
}

void tick() { previous_time = micros(); }

int32_t tack() {
  current_time = micros();
  return current_time - previous_time;
}
