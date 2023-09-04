#ifndef _POTMETER_HPP_
#define _POTMETER_HPP_

#include "SensorInterface.hpp"

class Potmeter : public SensorInterface {
 public:
  Potmeter(uint8_t analog_pin_init);
  ~Potmeter() override = default;
  int32_t getReadingValue() override;
  void setOffset(int32_t new_offset) override;

 private:
  uint8_t analog_pin_;
  int32_t offset_;
};

#endif  //_POTMETER_HPP_
