#ifndef _PEDALBOX_HPP_
#define _PEDALBOX_HPP_

#include <stdint.h>

#include <Joystick.h>
#include "Pedal.hpp"

class Pedalbox {
 public:
  Pedalbox();
  ~Pedalbox();
  void setBrakeSensor(SensorInterface* sensor);
  void setThrottleSensor(SensorInterface* sensor);
  void setClutchSensor(SensorInterface* sensor);
  void begin();
  void refreshValues();
  int32_t get_brake_value();
  int32_t get_throttle_value();
  int32_t get_clutch_value();
  void updateController();

 private:
  Joystick_ hid_controller;
  Pedal brake;
  Pedal throttle;
  Pedal clutch;
  int32_t brake_value;
  int32_t throttle_value;
  int32_t clutch_value;
};

#endif  //_PEDALBOX_HPP_
