#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Encoders encoders;

float wheelCirc = FLOAT; // change to the circumference that you measured for your robot

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

float getDistance(){
// Example for reading out the count from the wheels. Uncomment, compile and try out.
// Open the serial monitor and move the wheels by hand.
  /*
  int countsL = encoders.getCountsLeft();
  int countsR = encoders.getCountsRight();
  delay(500);
  Serial.println("Move my wheels.... counts L " + (String)countsL + " R " + (String)countsR);
  */
  return 0; // change to the distance calculated by your code
}

void loop() {
  float distance = getDistance();
  Serial.println("Distance travelled: " + (String)distance);
  }
