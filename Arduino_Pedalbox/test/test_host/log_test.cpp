#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Log.hpp>
#include <SerialInterface.hpp>
#include <TimeInterface.hpp>
#include <cstring>

using namespace testing;

class SerialMock : public SerialInterface {
 public:
  MOCK_METHOD(size_t, write, (const char* string_to_write), (override));
  MOCK_METHOD(void, begin, (unsigned long baud_rate), (override));
};

class TimeMock : public TimeInterface {
 public:
  MOCK_METHOD(void, SetTime,
              (int hour, int minute, int second, int day, int month, int year),
              (override));
  MOCK_METHOD(void, SetTime, (uint32_t time), (override));
  MOCK_METHOD(uint8_t, get_hour, (), (override));
  MOCK_METHOD(uint8_t, get_minute, (), (override));
  MOCK_METHOD(uint8_t, get_second, (), (override));
  MOCK_METHOD(uint16_t, get_millisecond, (), (override));
  MOCK_METHOD(void, update, (), (override));
};

TEST(LogTest, TC150SendLogMessageToSerialPort) {
  // Preconditions
  SerialMock serial_mock;
  TimeMock time_mock;
  Log log(&time_mock, &serial_mock);

  char file[] = "";
  int line = 0;
  char expected_message[] = "Hello World!";

  EXPECT_CALL(time_mock, get_hour()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_mock, get_minute()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_mock, get_second()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_mock, get_millisecond()).WillOnce(::testing::Return(0));

  // Expected behavior
  EXPECT_CALL(serial_mock, write(StrNe("")));

  // Action
  log.createLog(Log::kInfo, file, line, expected_message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}

TEST(LogTest, TC149TestLogMessageStructureWithZeroTime) {
  // Preconditions
  SerialMock serial_mock;
  TimeMock time_mock;
  Log log(&time_mock, &serial_mock);

  EXPECT_CALL(time_mock, get_hour()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_mock, get_minute()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_mock, get_second()).WillOnce(::testing::Return(0));
  EXPECT_CALL(time_mock, get_millisecond()).WillOnce(::testing::Return(0));

  // Expected behavior
  char time_str[] = "00:00:00.000";
  char log_type[] = "INFO";
  char file[] = "test/test_desktop/log_test.cpp";
  int line = 150;
  char message[] = "Send log message to serial port";
  char expected_log[100];
  sprintf(expected_log, "%s %s %s:%d: %s\n", time_str, log_type, file, line,
          message);
  EXPECT_CALL(serial_mock, write(StrEq(expected_log))).Times(1);

  // Action
  log.createLog(Log::kInfo, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}

TEST(LogTest, T149TestLogMessageStructureWithOneDigit) {
  // Preconditions
  SerialMock serial_mock;
  TimeMock time_mock;
  Log log(&time_mock, &serial_mock);

  EXPECT_CALL(time_mock, get_hour()).WillOnce(::testing::Return(1));
  EXPECT_CALL(time_mock, get_minute()).WillOnce(::testing::Return(1));
  EXPECT_CALL(time_mock, get_second()).WillOnce(::testing::Return(1));
  EXPECT_CALL(time_mock, get_millisecond()).WillOnce(::testing::Return(1));

  // Expected behavior
  char time_str[] = "01:01:01.001";
  char log_type[] = "WARNING";
  char file[] = "test/test_desktop/log_test.cpp";
  int line = 150;
  char message[] = "Send log message to serial port";
  char expected_log[100];
  sprintf(expected_log, "%s %s %s:%d: %s\n", time_str, log_type, file, line,
          message);
  EXPECT_CALL(serial_mock, write(StrEq(expected_log))).Times(1);

  // Action
  log.createLog(Log::kWarning, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}

TEST(LogTest, T149TestLogMessageStuctureWithTwoDigits) {
  // Preconditions
  SerialMock serial_mock;
  TimeMock time_mock;
  Log log(&time_mock, &serial_mock);

  EXPECT_CALL(time_mock, get_hour()).WillOnce(::testing::Return(11));
  EXPECT_CALL(time_mock, get_minute()).WillOnce(::testing::Return(11));
  EXPECT_CALL(time_mock, get_second()).WillOnce(::testing::Return(11));
  EXPECT_CALL(time_mock, get_millisecond()).WillOnce(::testing::Return(11));

  // Expected behavior
  char time_str[] = "11:11:11.011";
  char log_type[] = "ERROR";
  char file[] = "test/test_desktop/log_test.cpp";
  int line = 150;
  char message[] = "Send log message to serial port";
  char expected_log[100];
  sprintf(expected_log, "%s %s %s:%d: %s\n", time_str, log_type, file, line,
          message);
  EXPECT_CALL(serial_mock, write(StrEq(expected_log))).Times(1);

  // Action
  log.createLog(Log::kError, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}

TEST(LogTest, TC149TestLogMessageStructureWithMaxDigits) {
  // Preconditions
  SerialMock serial_mock;
  TimeMock time_mock;
  Log log(&time_mock, &serial_mock);

  EXPECT_CALL(time_mock, get_hour()).WillOnce(::testing::Return(23));
  EXPECT_CALL(time_mock, get_minute()).WillOnce(::testing::Return(59));
  EXPECT_CALL(time_mock, get_second()).WillOnce(::testing::Return(59));
  EXPECT_CALL(time_mock, get_millisecond()).WillOnce(::testing::Return(999));

  // Expected behavior
  char time_str[] = "23:59:59.999";
  char log_type[] = "DEBUG";
  char file[] = "test/test_desktop/log_test.cpp";
  int line = 150;
  char message[] = "Send log message to serial port";
  char expected_log[100];
  sprintf(expected_log, "%s %s %s:%d: %s\n", time_str, log_type, file, line,
          message);
  EXPECT_CALL(serial_mock, write(StrEq(expected_log))).Times(1);

  // Action
  log.createLog(Log::kDebug, file, line, message);

  ::testing::Mock::VerifyAndClearExpectations(&serial_mock);
}