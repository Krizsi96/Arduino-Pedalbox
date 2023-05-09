#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <log.h>

#include <cstring>

using ::testing::_;

TEST(LogTest, TC149LogMessageStructure) {
  // Preconditions
  ArduinoSerialMock serial_mock;
  ArduinoTimeInterface time;
  TimeLibMock time_lib;
  Log log(&time, &serial_mock, &time_lib);

  EXPECT_CALL(time_lib, get_hour()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_lib, get_minute()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_lib, get_second()).WillOnce(::testing::Return(0));

  // Expected behavior
  char time_str[] = "00:00:00.000";
  char log_type[] = "INFO";
  char file[] = "test/test_desktop/log_test.cpp";
  int line = 150;
  char message[] = "Send log message to serial port";
  char buffer[100];
  sprintf(buffer, "%s %s %s:%d: %s\n", time_str, log_type, file, line, message);
  const std::string expected = buffer;
  EXPECT_CALL(serial_mock, print(expected));

  // Action
  log.createLog(Log::kInfo, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}