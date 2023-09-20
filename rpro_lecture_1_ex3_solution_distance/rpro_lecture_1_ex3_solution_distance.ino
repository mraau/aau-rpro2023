#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Encoders encoders;
Zumo32U4Motors motors;

bool ledOn = true;
int speed = 100;
float wheelCirc = 13.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

float getDistance(){
  int countsL = encoders.getCountsLeft();
  int countsR = encoders.getCountsRight();

  float distanceL = countsL/900.0 * wheelCirc;
  float distanceR = countsR/900.0 * wheelCirc;

  Serial.println("Move my wheels.... counts L " + (String)countsL + " R " + (String)countsR);
  Serial.println("Move my wheels.... cm L " + (String)distanceL + " R " + (String)distanceR);

  delay(1000);

  return (distanceL + distanceR)/2;
}

void loop() {
  // Example for reading out the count from the wheels
  /*
  int countsL = encoders.getCountsLeft();
  int countsR = encoders.getCountsRight();
  delay(500);
  Serial.println("Move my wheels.... counts L " + (String)countsL + " R " + (String)countsR);
  */
  float distance = getDistance();
  Serial.println("Distance travelled: " + (String)distance);
  }
