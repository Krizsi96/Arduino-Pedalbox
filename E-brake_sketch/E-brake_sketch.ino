#include <Joystick.h>
float trustFactor = 0.3;
float prevEbrakeSensorValue = 0;
float prevBrakeSensorValue = 0;
float prevClutchSensorValue = 0;
float prevThrottleSensorValue = 0;

void setup() 
{
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  Joystick.begin();
  //Serial.begin(9600);
}


void loop() 
{
  float ThrottleSensorValue = analogRead(A1);
  float BrakeSensorValue = analogRead(A2);
  float ClutchSensorValue = analogRead(A3);
  float EbrakeSensorValue = analogRead(A0);
  float EbrakePos;
  float ThrottlePos;
  float BrakePos;
  float ClutchPos;
  float modBrakePos;
  
  EbrakePos = constrain(Filter(EbrakeSensorValue,prevEbrakeSensorValue),118,179);
  prevEbrakeSensorValue = EbrakePos;

  ThrottlePos = constrain(Filter(ThrottleSensorValue,prevThrottleSensorValue),160,980);
  prevThrottleSensorValue = ThrottlePos;

  BrakePos = constrain(Filter(BrakeSensorValue,prevBrakeSensorValue),490,965);
  prevBrakeSensorValue = BrakePos;
  if (BrakePos >= 858)
  {
    modBrakePos = BrakePos+500;
  }
  else
  {
    modBrakePos = 3.364*BrakePos-1537;
  }

  ClutchPos = constrain(Filter(ClutchSensorValue,prevClutchSensorValue),350,1000);
  prevClutchSensorValue = ClutchPos;
  
  int EbrakeMapped = map(EbrakePos,0,500,0,255);
  int ThrottleMapped = map(ThrottlePos,150,1000,0,255);
  int BrakeMapped = map(modBrakePos,0,1500,0,255);
  int ClutchMapped = map(ClutchPos,0,1023,100,355);
  Joystick.setXAxis(EbrakeMapped);
  Joystick.setXAxisRotation(ThrottleMapped);
  Joystick.setYAxisRotation(BrakeMapped);
  Joystick.setZAxis(ClutchMapped);
  //Serial.print(ClutchMapped);
  //Serial.print(",");
  //Serial.print(modBrakePos);
  //Serial.print(",");
  //Serial.print(BrakePos+500);
  //Serial.println();
}

int Filter(int Data, int PrevData){
  int filteredData;
  filteredData = trustFactor*Data+(1-trustFactor)*PrevData;
  return filteredData;
}

