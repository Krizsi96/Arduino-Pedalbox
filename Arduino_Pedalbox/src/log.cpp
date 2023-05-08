#include "log.h"

Log::Log()
    : start_time(1356998400),
      millis_counter(0),
      millisecond(0),
      second_counter(start_time),
      time_updated(false),
      Time_(new ArduinoTimeInterface()),
      TimeLib_(new TimeLibInterface()),
      Serial_(new ArduinoSerialInterface()) {
  TimeLib_->SetTime(start_time);
}

Log::Log(ArduinoTimeInterface* Time)
    : start_time(1356998400),
      millis_counter(0),
      millisecond(0),
      second_counter(start_time),
      time_updated(false),
      Time_(Time),
      TimeLib_(new TimeLibInterface()),
      Serial_(new ArduinoSerialInterface()) {
  TimeLib_->SetTime(start_time);
}

Log::Log(ArduinoSerialInterface* Serial)
    : start_time(1356998400),
      millis_counter(0),
      millisecond(0),
      second_counter(start_time),
      time_updated(false),
      Time_(new ArduinoTimeInterface()),
      TimeLib_(new TimeLibInterface()),
      Serial_(Serial) {
  TimeLib_->SetTime(start_time);
}

Log::Log(TimeLibInterface* TimeLib)
    : start_time(1356998400),
      millis_counter(0),
      millisecond(0),
      second_counter(start_time),
      time_updated(false),
      Time_(new ArduinoTimeInterface()),
      TimeLib_(TimeLib),
      Serial_(new ArduinoSerialInterface()) {
  TimeLib_->SetTime(start_time);
}

Log::Log(ArduinoTimeInterface* Time, ArduinoSerialInterface* Serial,
         TimeLibInterface* TimeLib)
    : start_time(1356998400),
      millis_counter(0),
      millisecond(0),
      second_counter(start_time),
      time_updated(false),
      Time_(Time),
      TimeLib_(TimeLib),
      Serial_(Serial) {
  TimeLib_->SetTime(start_time);
}

void Log::printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon and
  // leading 0
  Serial_->print(":");
  if (digits < 10) Serial_->print('0');
  Serial_->print(digits);
}

void Log::digitalClockDisplay() {
  // digital clock display of the time
  Serial_->print(TimeLib_->get_hour());
  printDigits(TimeLib_->get_minute());
  printDigits(TimeLib_->get_second());
  Serial_->print(".");
  if (millisecond < 10) {
    Serial_->print("00");
  } else if ((10 <= millisecond) && (millisecond < 100)) {
    Serial_->print("0");
  }
  Serial_->print(millisecond);
  Serial_->print(" ");
}

void Log::updateTime() {
  if (millis_counter % 1000 == 0) {  // every second
    if (!time_updated) {
      second_counter++;
      time_updated = true;
    }
  } else {
    time_updated = false;
  }
  TimeLib_->SetTime(second_counter);
  uint32_t seconds = (millis_counter / 1000) * 1000;
  millisecond = (second_counter - seconds);
  millis_counter = Time_->InMillis();
}

void Log::createLog(kLogType log_type, const char* file, int line,
                    const char* message) {
  char log_type_str[10];
  switch (log_type) {
    case kInfo:
      strcpy(log_type_str, "INFO");
      break;
    case kWarning:
      strcpy(log_type_str, "WARNING");
      break;
    case kError:
      strcpy(log_type_str, "ERROR");
      break;
    case kDebug:
      strcpy(log_type_str, "DEBUG");
      break;
    default:
      strcpy(log_type_str, "UNKNOWN");
      break;
  }

  // digitalClockDisplay();
  // Serial_->print(log_type_str);
  // Serial_->print(" ");
  // Serial_->print(file);
  // Serial_->print(":");
  // Serial_->print(line);
  // Serial_->print(": ");
  // Serial_->print(message);
  // Serial_->print("\n");

  char log_message[strlen(log_type_str) + strlen(file) + strlen(message) + 30];
  sprintf(log_message, "%s %s:%d: %s\n", log_type_str, file, line, message);

#ifdef HOST
  const std::string log_message_test = log_message;
  Serial_->print(log_message_test);
#else
  Serial_->print(log_message);
#endif
}