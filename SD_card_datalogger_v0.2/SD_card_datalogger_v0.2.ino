/*Datalogger which saves the mesured data on SD card in text format. You can set
  the frequency of the logger.

  The circuit:
  *analog sensors on analog pin 0 and 1
  *SD card attached to SPI bus:
  **MOSI - pin 11
  **MISO - pin 12
  **CLK - pin 13
  **CS - pin 10
  
  created Jan 2019
  by Kristof Kovacs
  version v0.2
 */

#include <SPI.h>
#include <SD.h>

const int pinCS = 10;
float t;

//The logging frequency
int Frequency = 1; //Hz
int Delay = 1000/Frequency; //ms
 
void setup() {
  Serial.begin(9600); //Open serial communications
  while (!Serial)
  {
    ; //wait for serial port to connect.
  }

  Serial.print("Initializing SD card... \n");

  //see if the card is present and can be initialized:
  if (!SD.begin(pinCS))
  {
    Serial.println("Card failed, or not present");
    while (!SD.begin(pinCS))
    {
      ; //don't do anything more, wait for a SD card
    }
  }
  
  
  Serial.println("card initialized.");
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  //delete the file from previous logging
  SD.remove("datalog.txt");

  //label the measurements
  File measurements = SD.open("datalog.txt", FILE_WRITE);
  if (measurements)
  {
    measurements.println("t,A0,A1");
    measurements.close();
    Serial.println("t,A0,A1");
  }


}

void loop() {

  //see if the card is presented and initialized
  //if (!SD.begin(pinCS))
  //{
  //  return;
  //}
  //make a string for assembling the data to log
  String dataString = "";

  //measuring the time during the logging
  t = float(millis())/1000;
  dataString += String(t);
  dataString += ",";
  
  //read two sensors and append to the string:
  for (int analogPin = 0; analogPin < 2; analogPin++)
  {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 1)
    {
      dataString += ",";
    }
  }

  //open the file. only one can be open at a time
  File dataFile = SD.open("datalog.txt", FILE_WRITE);  

  //if the file is available, write to it
  if (dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else
  {
    Serial.println("error opening datalog.txt");
  }

  //delay used for the logging frequency (1000 -> 1Hz)
  delay(Delay); 
}
