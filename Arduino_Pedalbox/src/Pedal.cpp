#include "Pedal.hpp"

Pedal::Pedal(std::shared_ptr<SensorInterface> sensor) : sensor_(sensor) {}

Pedal::Pedal() : sensor_(nullptr) {}

Pedal::~Pedal() {}

int32_t Pedal::readValue() { return sensor_->getReadingValue(); }

void Pedal::setOffset(int32_t new_offset) { sensor_->setOffset(new_offset); }

void Pedal::set_sensor(std::shared_ptr<SensorInterface> sensor) {
  sensor_ = sensor;
}

std::shared_ptr<SensorInterface> Pedal::get_sensor() { return sensor_; }

int32_t Pedal::RawReadingValue() { return sensor_->getRawReadingValue(); }
