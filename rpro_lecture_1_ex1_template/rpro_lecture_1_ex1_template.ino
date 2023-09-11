#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
bool ledOn;
int speed;

void setup() {
  // put your setup code here, to run once:

}

void ledBlink(){
  // Turn the LEDs on.
  ledRed(1);
  ledYellow(1);
  ledGreen(1);

  // Wait for a second.
  delay(1000);

  // Turn the LEDs off.
  ledRed(0);
  ledYellow(0);
  ledGreen(0);

  // Wait for a second.
  delay(1000);
}

void forward(){
  motors.setSpeeds(0, 0); //SPEED_OF_LEFT_MOTOR, SPEED_OF_RIGHT_MOTOR
  delay(1000);
  motors.setSpeeds(0,0);
}

void backward(){

}

void turnRight(){

}

void turnLeft(){

}

void loop() {
}
