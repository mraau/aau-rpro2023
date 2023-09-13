#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;

#define NUM_SENSORS 3
uint16_t lineSensorValues[NUM_SENSORS];

int speed = 50;
int threshold=500;
long randNumber;

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

void loop() {
  readLineSensors();
  if (lineSensorValues[0]<threshold && lineSensorValues[1] < threshold && lineSensorValues[2]< threshold) {
    forward();
  }
//   else stop();
  else randomTurn();
  delay(100);
}
