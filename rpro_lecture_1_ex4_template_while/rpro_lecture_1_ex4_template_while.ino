#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors;
Zumo32U4LineSensors lineSensors;
Zumo32U4LCD lcd;
Zumo32U4IMU imu;
Zumo32U4ButtonA buttonA;

#define NUM_SENSORS 3
uint16_t lineSensorValues[NUM_SENSORS];

int speed = 50;
int threshold=500;
long randNumber;

// variables for gyro
uint32_t turnAngle = 0;
int16_t turnRate;
int16_t gyroOffset;
uint16_t gyroLastUpdate = 0;

void setup() {
  lineSensors.initThreeSensors();
  Serial.begin(9600);
  randomSeed(analogRead(0));
  turnSensorSetup();
  delay(500);
}

void loop() {
  readLineSensors();
  if (lineSensorValues[0]<threshold && lineSensorValues[1] < threshold && lineSensorValues[2]< threshold) {
    forward();}
  else randomTurn();
  delay(100);
}

/* 
Line sensor functions 
*/
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

/* 
Drive functions
*/
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

void randomTurnByAngle(){
}

void randomTurnByAngleExtra(){
}

/* 
Gyro setup and convenience functions '
*/
void turnSensorSetup()
{
  Wire.begin();
  imu.init();
  imu.enableDefault();
  imu.configureForTurnSensing();

  lcd.clear();
  lcd.print(F("Gyro cal"));

  // Turn on the yellow LED in case the LCD is not available.
  ledYellow(1);

  // Delay to give the user time to remove their finger.
  delay(500);

  // Calibrate the gyro.
  int32_t total = 0;
  for (uint16_t i = 0; i < 1024; i++)
  {
    // Wait for new data to be available, then read it.
    while(!imu.gyroDataReady()) {}
    imu.readGyro();

    // Add the Z axis reading to the total.
    total += imu.g.z;
  }
  ledYellow(0);
  gyroOffset = total / 1024;

  // Display the angle (in degrees from -180 to 180) until the
  // user presses A.
  lcd.clear();
  turnSensorReset();
}

// This should be called to set the starting point for measuring
// a turn.  After calling this, turnAngle will be 0.
void turnSensorReset()
{
  gyroLastUpdate = micros();
  turnAngle = 0;
}

// Read the gyro and update the angle.  This should be called as
// frequently as possible while using the gyro to do turns.
void turnSensorUpdate()
{
  // Read the measurements from the gyro.
  imu.readGyro();
  turnRate = imu.g.z - gyroOffset;

  // Figure out how much time has passed since the last update (dt)
  uint16_t m = micros();
  uint16_t dt = m - gyroLastUpdate;
  gyroLastUpdate = m;

  // Multiply dt by turnRate in order to get an estimation of how
  // much the robot has turned since the last update.
  // (angular change = angular velocity * time)
  int32_t d = (int32_t)turnRate * dt;

  // The units of d are gyro digits times microseconds.  We need
  // to convert those to the units of turnAngle, where 2^29 units
  // represents 45 degrees.  The conversion from gyro digits to
  // degrees per second (dps) is determined by the sensitivity of
  // the gyro: 0.07 degrees per second per digit.
  //
  // (0.07 dps/digit) * (1/1000000 s/us) * (2^29/45 unit/degree)
  // = 14680064/17578125 unit/(digit*us)
  turnAngle += (int64_t)d * 14680064 / 17578125;
}

int32_t getTurnAngleInDegrees(){
  turnSensorUpdate();
  // do some math and pointer magic to turn angle in seconds to angle in degree
  return (((int32_t)turnAngle >> 16) * 360) >> 16;
}
