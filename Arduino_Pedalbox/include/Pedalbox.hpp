#ifndef _PEDALBOX_HPP_
#define _PEDALBOX_HPP_

#include <ArxSmartPtr.h>
#include <Joystick.h>
#include <stdint.h>

#include "Pedal.hpp"

class Pedalbox {
 public:
  Pedalbox();
  ~Pedalbox();
  void setBrakeSensor(std::shared_ptr<SensorInterface> sensor);
  void setThrottleSensor(std::shared_ptr<SensorInterface> sensor);
  void setClutchSensor(std::shared_ptr<SensorInterface> sensor);
  void begin();
  void refreshValues();
  int32_t get_brake_value();
  int32_t get_throttle_value();
  int32_t get_clutch_value();
  void updateController();
  int32_t get_raw_brake_value();
  int32_t get_raw_throttle_value();
  int32_t get_raw_clutch_value();

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
