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
  int hour = TimeLib_->get_hour();
  int minute = TimeLib_->get_minute();
  int second = TimeLib_->get_second();

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

  char log_message[strlen(log_type_str) + strlen(file) + strlen(message) + 30];
  sprintf(log_message, "%02d:%02d:%02d.%03u %s %s:%d: %s\n", hour, minute,
          second, millisecond, log_type_str, file, line, message);

#ifdef HOST
  const std::string log_message_test = log_message;
  Serial_->print(log_message_test);
#else
  Serial_->print(log_message);
#endif
}