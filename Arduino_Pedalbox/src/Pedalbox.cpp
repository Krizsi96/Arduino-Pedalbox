#include "Pedalbox.hpp"

Pedalbox::Pedalbox() {
  brake = Pedal();
  throttle = Pedal();
  clutch = Pedal();
  brake_value = 0;
  throttle_value = 0;
  clutch_value = 0;
}

Pedalbox::~Pedalbox() {}

void Pedalbox::setBrakeSensor(SensorInterface* sensor) {
  brake.set_sensor(sensor);
}

void Pedalbox::setThrottleSensor(SensorInterface* sensor) {
  throttle.set_sensor(sensor);
}

void Pedalbox::setClutchSensor(SensorInterface* sensor) {
  clutch.set_sensor(sensor);
}

void Pedalbox::begin() {
  if (brake.get_sensor() != nullptr && throttle.get_sensor() != nullptr &&
      clutch.get_sensor() != nullptr)
    hid_controller.begin();
  else
    Serial.println("ERROR: Pedalbox sensors not set!");
}

void Pedalbox::refreshValues() {
  brake_value = brake.readValue();
  throttle_value = throttle.readValue();
  clutch_value = clutch.readValue();
}

int32_t Pedalbox::get_brake_value() { return brake_value; }

int32_t Pedalbox::get_throttle_value() { return throttle_value; }

int32_t Pedalbox::get_clutch_value() { return clutch_value; }
