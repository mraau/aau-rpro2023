#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Encoders encoders;

#define NUM_SENSORS 3
uint16_t lineSensorValues[NUM_SENSORS];

int speed = 50;
int threshold=500;
float wheelCirc = 13.0;
long randNumber;
bool ledOn = true;

void setup() {
  // put your setup code here, to run once:
  lineSensors.initThreeSensors();
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

// Prints a line with all the sensor readings to the serial
// monitor.
void printReadingsToSerial()
{
  char buffer[80];
  sprintf(buffer, "%4d %4d %4d\n",
    lineSensorValues[0],
    lineSensorValues[1],
    lineSensorValues[2]
  );
  Serial.print(buffer);
}

// the uncalibrated line sensor reading are between 0 (very bright) and 2000 (very dark)
void readLineSensors(){
  lineSensors.read(lineSensorValues, QTR_EMITTERS_ON);
  printReadingsToSerial();
}

void flashLEDs(){
  ledRed(ledOn);
  delay(300);
  ledRed(!ledOn);
  ledYellow(ledOn);
  delay(300);
  ledYellow(!ledOn);
  ledGreen(ledOn);
  delay(300);
  ledGreen(!ledOn);
}

float getDistance(){
  int countsL = encoders.getCountsLeft();
  int countsR = encoders.getCountsRight();

  float distanceL = countsL/900.0 * wheelCirc;
  float distanceR = countsR/900.0 * wheelCirc;

  //Serial.println("Move my wheels.... counts L " + (String)countsL + " R " + (String)countsR);
  //Serial.println("Move my wheels.... cm L " + (String)distanceL + " R " + (String)distanceR);

  //delay(1000);
  return (distanceL + distanceR)/2;
}

void resetEncoders(){
  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();
}

void stop(){
  motors.setSpeeds(0,0);
}

void forward(){
  motors.setSpeeds(speed, speed);
}

void randomTurn(){
  randNumber = random(300,500);
  long dir = random(1,3);
  if (dir == 1)
    motors.setSpeeds(200,-200);
  else motors.setSpeeds(-200,200);
  delay(randNumber);
  motors.setSpeeds(0,0);
}

void randomTurnLeft(){
  randNumber = random(300,500);
  motors.setSpeeds(-200,200);
  delay(randNumber);
  motors.setSpeeds(0,0);
}

void randomTurnRight(){
  randNumber = random(300,500);
  motors.setSpeeds(200, -200);
  delay(randNumber);
  motors.setSpeeds(0,0);
}

void turn(int t){

}

void loop() {
  readLineSensors();
  if (lineSensorValues[0]<threshold && lineSensorValues[1] < threshold && lineSensorValues[2]< threshold) {
    forward();
  }
//   else stop();
  else if (getDistance()<50) {
    ledGreen(ledOn);
    turn(2);
  } else if (getDistance()<100){
    ledYellow(ledOn);
    ledGreen(!ledOn);
    turn(1);
  } else if (getDistance()<150){
    ledRed(ledOn);
    ledYellow(!ledOn);
    turn(3);
  } else {
    stop();
    flashLEDs();
    flashLEDs();    
    flashLEDs();    
    flashLEDs();    
    flashLEDs();
    resetEncoders();
    ledGreen(ledOn);
  }
  delay(100);
}
