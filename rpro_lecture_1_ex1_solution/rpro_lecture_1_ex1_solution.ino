#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
bool ledOn = true;
int speed = 100;

void setup() {
  // put your setup code here, to run once:

}

void ledBlink(){
  // Turn the LEDs on.
  ledRed(ledOn);
  ledYellow(ledOn);
  ledGreen(ledOn);

  // Wait for a second.
  delay(1000);

  // Turn the LEDs off.
  ledRed(!ledOn);
  ledYellow(!ledOn);
  ledGreen(!ledOn);

  // Wait for a second.
  delay(1000);
}

void forward(){
  ledRed(ledOn);
  motors.setSpeeds(speed, speed);
  delay(1000);
  motors.setSpeeds(0,0);
  ledRed(!ledOn);
}

void backward(){
  ledYellow(ledOn);
  motors.setSpeeds(-speed, -speed);
  delay(1000);
  motors.setSpeeds(0,0);
  ledYellow(!ledOn);
}

// not turning at 90 degrees, adjust speed and/or delay
void turnRight(){
  ledGreen(ledOn);
  motors.setSpeeds(-speed, speed);
  delay(1000);
  motors.setSpeeds(0,0);
  ledGreen(!ledOn);
}

// not turning at 90 degrees, adjust speed and/or delay
void turnLeft(){
  ledGreen(ledOn);
  motors.setSpeeds(speed, -speed);
  delay(1000);
  motors.setSpeeds(0,0);
  ledGreen(!ledOn);
}

void driveSquare(){
  forward();
  turnLeft();
  forward();
  turnLeft();
  forward();
  turnLeft();
  forward();
}

void loop() {
  ledBlink();
  forward();
}
