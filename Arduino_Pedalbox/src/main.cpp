#include <arduino-timer.h>

#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedalbox.hpp"
#include "Potmeter.hpp"
#include "SensorConfig.h"
#include "board_pinout.h"
#include "jled.h"

enum RGB { RED, GREEN, BLUE };

ArduinoWrapper arduino;

auto timer = timer_create_default();
int32_t previous_time = 0;
int32_t current_time = 0;
int32_t cycle_time = 0;

LoadCell brake_load_cell(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
Potmeter throttle_potmeter(THROTTLE_PEDAL_PIN);
Potmeter clutch_potmeter(CLUTCH_PEDAL_PIN);

Pedalbox pedalbox;

JLed rgb_led[] = {JLed(RGB_RED_PIN).Off(), JLed(RGB_GREEN_PIN).Off(),
                  JLed(RGB_BLUE_PIN).Off()};

JLedSequence rgb_sequence(JLedSequence::eMode::PARALLEL, rgb_led);

bool showPedalReadings(void *);
bool updateGameController(void *);
void sensorConfiguration();
void tick();
int32_t tack();
void InitModeRgb();
void HearthbeatModeRgb();

void setup() {
  InitModeRgb();
  Serial.begin(9600);
  sensorConfiguration();
  pedalbox.setBrakeSensor(&brake_load_cell);
  pedalbox.setThrottleSensor(&throttle_potmeter);
  pedalbox.setClutchSensor(&clutch_potmeter);
  pedalbox.begin();

  timer.every(100, showPedalReadings);
  timer.every(50, updateGameController);

  HearthbeatModeRgb();
}

void loop() {
  rgb_sequence.Update();
  timer.tick();

  tick();
  pedalbox.refreshValues();
}

bool showPedalReadings(void *) {
  Serial.print(">brake_filtered:");
  Serial.println(pedalbox.get_brake_value());

  Serial.print(">throttle_filtered:");
  Serial.println(pedalbox.get_throttle_value());
  Serial.print(">throttle_raw:");
  Serial.println(analogRead(THROTTLE_PEDAL_PIN));

  Serial.print(">clutch_filtered:");
  Serial.println(pedalbox.get_clutch_value());
  Serial.print(">clutch_raw:");
  Serial.println(analogRead(CLUTCH_PEDAL_PIN));

  Serial.print("cycle time: ");
  Serial.println(cycle_time);

  return true;
}

bool updateGameController(void *) {
  pedalbox.updateController();
  cycle_time = tack();
  return true;
}

void tick() { previous_time = micros(); }

int32_t tack() {
  current_time = micros();
  return current_time - previous_time;
}

void sensorConfiguration() {
  brake_load_cell.setOffset(BRAKE_PEDAL_OFFSET);
  throttle_potmeter.setOffset(THROTTLE_PEDAL_OFFSET);
  clutch_potmeter.setOffset(CLUTCH_PEDAL_OFFSET);

  brake_load_cell.setFilter(BRAKE_PEDAL_FILTER_TYPE,
                            BRAKE_PEDAL_FILTER_FREQUENCY,
                            BRAKE_PEDAL_INITIAL_VALUE);
  throttle_potmeter.setFilter(THROTTLE_PEDAL_FILTER_TYPE,
                              THROTTLE_PEDAL_FILTER_FREQUENCY,
                              THROTTLE_PEDAL_INITIAL_VALUE);
  clutch_potmeter.setFilter(CLUTCH_PEDAL_FILTER_TYPE,
                            CLUTCH_PEDAL_FILTER_FREQUENCY,
                            CLUTCH_PEDAL_INITIAL_VALUE);
}

void InitModeRgb() {
  rgb_led[RED].Off();
  rgb_led[GREEN].Off();
  rgb_led[BLUE].Breathe(500).Forever();
  rgb_sequence = JLedSequence(JLedSequence::eMode::PARALLEL, rgb_led);
  rgb_sequence.Update();
}

void HearthbeatModeRgb() {
  int heartbeat_period = 2500;
  rgb_led[RED].Breathe(heartbeat_period).Forever();
  rgb_led[GREEN].Breathe(heartbeat_period).Forever();
  rgb_led[BLUE].Breathe(heartbeat_period).Forever();
  rgb_sequence = JLedSequence(JLedSequence::eMode::PARALLEL, rgb_led);
  rgb_sequence.Update();
}
