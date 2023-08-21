#include "ArduinoWrapper.hpp"
#include "LoadCell.hpp"

#define HX711_DOUT 10
#define HX711_SCK 9

ArduinoWrapper arduino;
long time = 0;
long previous_time = 0;

LoadCell load_cell(HX711_SCK, HX711_DOUT);

void setup() {
  Serial.begin(9600);
  load_cell.begin();
  load_cell.updateOffset(12000);
}

void loop() {
  time = millis();
  if ((time - previous_time) > 1000) {
    previous_time = time;
    int32_t load_cell_reading = load_cell.getReadingValue();
    Serial.println(load_cell_reading);
  }
}