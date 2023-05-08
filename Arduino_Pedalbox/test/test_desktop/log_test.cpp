#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <log.h>

#include <cstring>

using ::testing::_;

TEST(LogTest, TC150_SendLogMessageToSerialPort) {
  // Setup
  ArduinoSerialMock serial_mock;
  ArduinoTimeInterface time;
  TimeLibInterface time_lib;
  Log log(&time, &serial_mock, &time_lib);

  char time_str[] = "00:00:00.000";
  char log_type[] = "INFO";
  char file[] = "test/test_desktop/log_test.cpp";
  int line = 150;
  char message[] = "Send log message to serial port";
  char buffer[100];
  sprintf(buffer, "%s %s:%d: %s\n", log_type, file, line, message);
  const std::string expected = buffer;

  EXPECT_CALL(serial_mock, print(expected));

  log.createLog(Log::kInfo, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}