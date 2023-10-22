#include "Log.hpp"

Log::Log(TimeInterface* Time, SerialInterface* Serial)
    : Serial_(Serial), Time_(Time) {}

Log::~Log() {}

void Log::createLog(kLogType log_type, const char* file, int line,
                    const char* message) {
  uint8_t hour = Time_->get_hour();
  uint8_t minute = Time_->get_minute();
  uint8_t second = Time_->get_second();
  uint16_t millisecond = Time_->get_millisecond();

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

  Serial_->write(log_message);
}