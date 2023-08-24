#include "Pedal.hpp"

Pedal::Pedal(SensorInterface* sensor) : sensor_(sensor) {}

Pedal::~Pedal() {}

int32_t Pedal::readValue() { return sensor_->getReadingValue(); }

void Pedal::setOffset(int32_t new_offset) { sensor_->setOffset(new_offset); }
