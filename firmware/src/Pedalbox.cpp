#include "Pedalbox.hpp"

#include "configs.h"

#define AUTO_SEND_STATE false

Pedalbox::Pedalbox()
    : hid_controller(0x11, JOYSTICK_TYPE_JOYSTICK, 0,
                     0,                    // Button Count, Hat Switch Count
                     false, false, false,  // X and Y, Z Axis
                     true, true, true,     // Rx, Ry, or Rz
                     false, false,         // rudder, throttle
                     false, false,         // accelerator, brake
                     false                 // steering
      ) {
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
    hid_controller.begin(AUTO_SEND_STATE);
  else
    Serial.println("ERROR: Pedalbox sensors not set!");

  hid_controller.setRxAxisRange(0, 65535);
  hid_controller.setRyAxisRange(0, 65535);
  hid_controller.setRzAxisRange(0, 65535);
}

void Pedalbox::refreshValues() {
  int32_t unmapped_brake_value = brake.readValue();
  int32_t unmapped_throttle_value = throttle.readValue();
  int32_t unmapped_clutch_value = clutch.readValue();

  brake_value = unmapped_brake_value / (BRAKE_RANGE_MAX / 65535);
  throttle_value = map(unmapped_throttle_value, THROTTLE_RANGE_MIN,
                       THROTTLE_RANGE_MAX, 0, 65535);
  clutch_value =
      map(unmapped_clutch_value, CLUTCH_RANGE_MIN, CLUTCH_RANGE_MAX, 0, 65535);
}

int32_t Pedalbox::get_brake_value() { return brake_value; }

int32_t Pedalbox::get_throttle_value() { return throttle_value; }

int32_t Pedalbox::get_clutch_value() { return clutch_value; }

void Pedalbox::updateController() {
  hid_controller.setRxAxis(throttle_value);
  hid_controller.setRyAxis(brake_value);
  hid_controller.setRzAxis(clutch_value);
  hid_controller.sendState();
}