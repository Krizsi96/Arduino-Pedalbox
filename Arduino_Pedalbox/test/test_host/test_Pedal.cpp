#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Pedal.hpp"
#include "SensorInterface.hpp"

using namespace testing;

class SensorMock : public SensorInterface {
 public:
  MOCK_METHOD(int32_t, getReadingValue, (), (override));
  MOCK_METHOD(void, setOffset, (int32_t new_offset), (override));
};

TEST(PedalInitialization, pedalInitializedWithSensor) {
  // Given
  SensorMock sensor_mock;

  // When
  Pedal pedal(&sensor_mock);

  // Then
  EXPECT_EQ(pedal.get_sensor(), &sensor_mock);
}

TEST(PedalInitialization, pedalInitializedWithoutSensor) {
  // When
  Pedal pedal;

  // Then
  EXPECT_EQ(pedal.get_sensor(), nullptr);
}

TEST(PedalSensorSetting, setSensorForPedal) {
  // Given
  SensorMock sensor_mock;
  Pedal pedal;

  // When
  pedal.set_sensor(&sensor_mock);

  // Then
  EXPECT_EQ(pedal.get_sensor(), &sensor_mock);
}

TEST(PedalSensorReading, readSensorValue) {
  // Given
  SensorMock sensor_mock;
  Pedal pedal(&sensor_mock);

  // Expected behavior
  EXPECT_CALL(sensor_mock, getReadingValue());

  // When
  pedal.readValue();

  // Then
  ::testing::Mock::VerifyAndClearExpectations(&sensor_mock);
}

TEST(PedalSensorOffsetSetting, setSensorOffset) {
  // Given
  SensorMock sensor_mock;
  Pedal pedal(&sensor_mock);
  int32_t offset = 100;

  // Expected behavior
  EXPECT_CALL(sensor_mock, setOffset(offset));

  // When
  pedal.setOffset(offset);

  // Then
  ::testing::Mock::VerifyAndClearExpectations(&sensor_mock);
}