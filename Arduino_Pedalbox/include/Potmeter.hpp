#ifndef _POTMETER_HPP_
#define _POTMETER_HPP_

#include <Filters.h>

#include "SensorInterface.hpp"

class Potmeter : public SensorInterface {
 public:
  Potmeter(uint8_t analog_pin_init);
  ~Potmeter() override = default;
  int32_t getReadingValue() override;
  void setOffset(int32_t new_offset) override;
  void setFilter(FILTER_TYPE filter_type, float cut_off_frequency,
                 float initial_value);
  int32_t getRawReadingValue();

 private:
  uint8_t analog_pin_;
  int32_t offset_;
  FilterOnePole filter_;
  int32_t applyFilterTo(int32_t raw_reading);
};

#endif  //_POTMETER_HPP_
