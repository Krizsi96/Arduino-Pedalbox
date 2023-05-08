#include "fake_arduino.hpp"

SerialCommunication::SerialCommunication() {}

SerialCommunication::~SerialCommunication() {}

void SerialCommunication::begin(int baud_rate) {}

void SerialCommunication::print(const char* str) {}

void SerialCommunication::print(int number) {}

void delay(int milliseconds) {}

void delayMicroseconds(int microseconds) {}

unsigned long millis() { return 0; }

unsigned long micros() { return 0; }