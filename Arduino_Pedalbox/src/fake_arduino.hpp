#pragma once

class SerialCommunication {
 public:
  SerialCommunication();
  ~SerialCommunication();
  void print(const char* str);
  void print(int number);
  void begin(int baud_rate);
};

inline SerialCommunication Serial;

extern void delay(int milliseconds);
extern void delayMicroseconds(int microseconds);
extern unsigned long millis();
extern unsigned long micros();