#ifndef _TIMEINTERFACE_H_
#define _TIMEINTERFACE_H_

class TimeInterface {
 public:
  virtual ~TimeInterface(){};
  virtual void SetTime(int hour, int minute, int second, int day, int month,
                       int year) = 0;
  virtual void SetTime(uint32_t time) = 0;
  virtual uint8_t get_hour() = 0;
  virtual uint8_t get_minute() = 0;
  virtual uint8_t get_second() = 0;
  virtual uint16_t get_millisecond() = 0;
  virtual void update() = 0;
};

#endif  //_TIMEINTERFACE_H_