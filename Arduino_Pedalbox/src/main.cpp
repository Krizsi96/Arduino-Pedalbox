#include <ArxSmartPtr.h>
#include <arduino-timer.h>

#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"
#include "Pedalbox.hpp"
#include "Potmeter.hpp"
#include "SensorConfig.h"
#include "board_pinout.h"
#include "jled.h"
#include "stopwatch.hpp"

enum RGB { RED, GREEN, BLUE };

ArduinoWrapper arduino;

auto timer = timer_create_default();
int32_t cycle_time = 0;

Pedalbox pedalbox;

JLed rgb_led[] = {JLed(RGB_RED_PIN).Off(), JLed(RGB_GREEN_PIN).Off(),
                  JLed(RGB_BLUE_PIN).Off()};

JLedSequence rgb_sequence(JLedSequence::eMode::PARALLEL, rgb_led);

Stopwatch measure_cycle_time;

bool showPedalReadings(void *);
bool updateGameController(void *);
void sensorConfiguration();
void InitModeRgb();
void HearthbeatModeRgb();

void setup() {
  InitModeRgb();
  Serial.begin(9600);
  sensorConfiguration();
  pedalbox.begin();

  timer.every(100, showPedalReadings);
  timer.every(50, updateGameController);

  HearthbeatModeRgb();
}

void loop() {
  rgb_sequence.Update();
  timer.tick();

  measure_cycle_time.start();
  pedalbox.refreshValues();
}

bool showPedalReadings(void *) {
  Serial.print(">brake_filtered:");
  Serial.println(pedalbox.get_brake_value());
  Serial.print(">brake_raw:");
  Serial.println(pedalbox.get_raw_brake_value());

  Serial.print(">throttle_filtered:");
  Serial.println(pedalbox.get_throttle_value());
  Serial.print(">throttle_raw:");
  Serial.println(pedalbox.get_raw_throttle_value());

  Serial.print(">clutch_filtered:");
  Serial.println(pedalbox.get_clutch_value());
  Serial.print(">clutch_raw:");
  Serial.println(pedalbox.get_raw_clutch_value());

  Serial.print("cycle time: ");
  Serial.println(cycle_time);

  return true;
}

bool updateGameController(void *) {
  pedalbox.updateController();
  cycle_time = measure_cycle_time.stop();
  return true;
}

void sensorConfiguration() {
  std::shared_ptr<SensorInterface> brake =
      std::make_shared<LoadCell>(BRAKE_PEDAL_SCK, BRAKE_PEDAL_DOUT);
  std::shared_ptr<SensorInterface> throttle =
      std::make_shared<Potmeter>(THROTTLE_PEDAL_PIN);
  std::shared_ptr<SensorInterface> clutch =
      std::make_shared<Potmeter>(CLUTCH_PEDAL_PIN);

  brake->setOffset(BRAKE_PEDAL_OFFSET);
  throttle->setOffset(THROTTLE_PEDAL_OFFSET);
  clutch->setOffset(CLUTCH_PEDAL_OFFSET);

  brake->setFilter(BRAKE_PEDAL_FILTER_TYPE, BRAKE_PEDAL_FILTER_FREQUENCY,
                   BRAKE_PEDAL_INITIAL_VALUE);
  throttle->setFilter(THROTTLE_PEDAL_FILTER_TYPE,
                      THROTTLE_PEDAL_FILTER_FREQUENCY,
                      THROTTLE_PEDAL_INITIAL_VALUE);
  clutch->setFilter(CLUTCH_PEDAL_FILTER_TYPE, CLUTCH_PEDAL_FILTER_FREQUENCY,
                    CLUTCH_PEDAL_INITIAL_VALUE);

  pedalbox.setBrakeSensor(brake);
  pedalbox.setThrottleSensor(throttle);
  pedalbox.setClutchSensor(clutch);
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
  rgb_led[RED].Off();
  rgb_led[GREEN].Breathe(heartbeat_period).Forever();
  rgb_led[BLUE].On();
  rgb_sequence = JLedSequence(JLedSequence::eMode::PARALLEL, rgb_led);
  rgb_sequence.Update();
}
