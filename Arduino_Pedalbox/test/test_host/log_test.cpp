#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <log.h>

#include <cstring>

using namespace testing;

TEST(LogTest, TC150SendLogMessageToSerialPort) {
  // Preconditions
  ArduinoSerialMock serial_mock;
  ArduinoTimeInterface time;
  TimeLibMock time_lib;
  Log log(&time, &serial_mock, &time_lib);

  char file[] = "";
  int line = 0;
  char expected_message[] = "Hello World!";

  EXPECT_CALL(time_lib, get_hour()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_lib, get_minute()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_lib, get_second()).WillOnce(::testing::Return(0));

  // Expected behavior
  EXPECT_CALL(serial_mock, print(StrNe("")));

  // Action
  log.createLog(Log::kInfo, file, line, expected_message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}

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
  char expected_log[100];
  sprintf(expected_log, "%s %s %s:%d: %s\n", time_str, log_type, file, line,
          message);
  EXPECT_CALL(serial_mock, print(StrEq(expected_log))).Times(1);

  // Action
  log.createLog(Log::kInfo, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}