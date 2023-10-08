#include "Pedalbox.hpp"

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

void Pedalbox::setBrakeSensor(std::shared_ptr<SensorInterface> sensor) {
  brake.set_sensor(sensor);
}

void Pedalbox::setThrottleSensor(std::shared_ptr<SensorInterface> sensor) {
  throttle.set_sensor(sensor);
}

void Pedalbox::setClutchSensor(std::shared_ptr<SensorInterface> sensor) {
  clutch.set_sensor(sensor);
}

void Pedalbox::begin() {
  if (brake.get_sensor() != nullptr && throttle.get_sensor() != nullptr &&
      clutch.get_sensor() != nullptr)
    hid_controller.begin(AUTO_SEND_STATE);
  else
    Serial.println("ERROR: Pedalbox sensors not set!");

  hid_controller.setRxAxisRange(0, 390);
  hid_controller.setRyAxisRange(2000, 67000);
  hid_controller.setRzAxisRange(0, 280);
}

void Pedalbox::refreshValues() {
  brake_value = brake.readValue();
  throttle_value = throttle.readValue();
  clutch_value = clutch.readValue();
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

int32_t Pedalbox::get_raw_brake_value() { return brake.RawReadingValue(); }

int32_t Pedalbox::get_raw_throttle_value() {
  return throttle.RawReadingValue();
}

int32_t Pedalbox::get_raw_clutch_value() { return clutch.RawReadingValue(); }
