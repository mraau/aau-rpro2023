#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 3
uint16_t lineSensorValues[NUM_SENSORS];
int s1, s2, s3;

int speed = 50;
int threshold;

void setup() {
  // put your setup code here, to run once:
  lineSensors.initThreeSensors();
  Serial.begin(9600);
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

void stop(){
  motors.setSpeeds(0,0);
}

void forward(){
  motors.setSpeeds(speed, speed);
}

// let the robot turn randomly, use the random function for this. The min and max values, 
// e.g. random(1,11) generates a number between 1 and 10
void randomTurn(){
//  randNumber = random(MIN, MAX+1);
}

void loop() {
  readLineSensors();
  // here comes your if-else statement
  /*
  if(){

  }
  else{

  }
  */
  delay(100);
}
