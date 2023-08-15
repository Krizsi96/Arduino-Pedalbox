#include "ArduinoWrapper.hpp"
#include "Log.hpp"

#define BUTTON_PIN 5

ArduinoWrapper arduino;
Log logging(&arduino.Time, &arduino.Serial);
long time = 0;
long previous_time = 0;
bool button_pressed = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(BUTTON_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  arduino.Time.update();

  time = millis();
  if ((time - previous_time) > 1000) {
    previous_time = time;
    logging.createLog(logging.kInfo, __FILE__, __LINE__, "one second passed");
  }

  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (!button_pressed) {
      logging.createLog(logging.kDebug, __FILE__, __LINE__, "button pressed");
      button_pressed = true;
    }
  } else {
    if (button_pressed) {
      logging.createLog(logging.kDebug, __FILE__, __LINE__, "button released");
      button_pressed = false;
    }
  }
}