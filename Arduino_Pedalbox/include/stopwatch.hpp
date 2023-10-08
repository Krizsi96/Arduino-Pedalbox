#ifndef _STOPWATCH_HPP_
#define _STOPWATCH_HPP_

#include <Arduino.h>
#include <stdint.h>

class Stopwatch {
 public:
  void start() { start_time_ = micros(); };
  uint32_t stop() {
    uint32_t elapsed_time = 0;
    if (start_time_ != 0) {
      stop_time_ = micros();
      elapsed_time = stop_time_ - start_time_;
    }
    start_time_ = 0;
    stop_time_ = 0;
    return elapsed_time;
  };

 private:
  uint32_t start_time_ = 0;
  uint32_t stop_time_ = 0;
};

#endif  //_STOPWATCH_HPP_