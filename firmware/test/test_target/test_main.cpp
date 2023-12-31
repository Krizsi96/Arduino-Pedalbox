#include <LiquidCrystal.h>
#include <arduino-timer.h>
#include <unity.h>

#include <ArduinoWrapper.hpp>

#include "ArduinoWrapper_test.hpp"
#include "testConfiguration.h"
#include "test_SensorInterface.hpp"

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
auto timer = timer_create_default();

void printTestInfo(uint8_t number, const char* test_name);
bool TurnOnBacklight(void*);
bool TurnOffBacklight(void*);

void setup() {
  Serial.begin(9600);

  TurnOnBacklight(nullptr);

  while (!Serial) {
    {
    }  // wait for serial port to connect. Needed for native USB port only
  }

  lcd.begin(16, 2);
  lcd.print("Starting tests...");
  UNITY_BEGIN();

  lcd.clear();
  lcd.print("ArduinoWrapper tests");

  printTestInfo(1, "test_if_hour_is_set_correctly");
  RUN_TEST(test_if_hour_is_set_correctly);

  printTestInfo(2, "test_if_minute_is_set_correctly");
  RUN_TEST(test_if_minute_is_set_correctly);

  printTestInfo(3, "test_if_second_is_set_correctly");
  RUN_TEST(test_if_second_is_set_correctly);

  printTestInfo(4, "test_if_hour_is_set_correctly_with_unix_time");
  RUN_TEST(test_if_hour_is_set_correctly_with_unix_time);

  printTestInfo(5, "test_if_minute_is_set_correctly_with_unix_time");
  RUN_TEST(test_if_minute_is_set_correctly_with_unix_time);

  printTestInfo(6, "test_if_second_is_set_correctly_with_unix_time");
  RUN_TEST(test_if_second_is_set_correctly_with_unix_time);

  printTestInfo(7, "test_if_time_is_updated");
  RUN_TEST(test_if_time_is_updated);

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("SensorInterface tests");

  printTestInfo(8, "read_potmeter_value");
  RUN_TEST(read_potmeter_value);

  printTestInfo(9, "set_offset_for_potmeter");
  RUN_TEST(set_offset_for_potmeter);

  printTestInfo(10, "read_load_cell_value");
  RUN_TEST(read_load_cell_value);

  printTestInfo(11, "set_offset_for_load_cell");
  RUN_TEST(set_offset_for_load_cell);

  UNITY_END();

  lcd.clear();
  lcd.print("Tests finished!");

  timer.in(5000, TurnOffBacklight);
}

void loop() {
  timer.tick();
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}

void printTestInfo(uint8_t number, const char* test_name) {
  lcd.clear();
  lcd.print("Test ");
  lcd.print(number);
  lcd.print("/9");
  lcd.setCursor(0, 1);
  lcd.print(test_name);
}

bool TurnOnBacklight(void*) {
  pinMode(LCD_BACKLIGHT_PIN, OUTPUT);
  digitalWrite(LCD_BACKLIGHT_PIN, HIGH);
  return true;
}

bool TurnOffBacklight(void*) {
  digitalWrite(LCD_BACKLIGHT_PIN, LOW);
  return true;
}
