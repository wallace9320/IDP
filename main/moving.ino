// Line follower
// TODO - 1. read line sensor
//      - 2. set motors based on line sensor readings

setMotors robot; // created class

// LS pins (analog input)
const int leftLSPin = A0;
const int rightLSPin = A1;

// timing LS - better way than using delay function
unsigned long lineSensorCm; // line sensor current millis
unsigned long lineSensorPm; // line sensor previous millis
const int LS_PERIOD = 50;   // checking line sensor value in every 50 ms

// timing Motor
unsigned long motorCm;
unsigned long motorPm;
const int MOTOR_PERIOD = 50; // updating motor speeds in every 50ms

// debug purpose, when we change to true, it will print out values that sensor reads on serial monitor
bool LSDebug = false;
bool MotorDebug = false;

// initialise the line sensor values
int leftLSReading = 0;
int rightLSReading = 0;
const int LS_THRESHOLD = 500; // distinguish black and white colour

// function for reading line sensor values and moving the robot
void readLSAndMove()
{
  // to avoid using delay() -> reading line sensor values in every LS_PERIOD
  lineSensorCm = millis();
  if (lineSensorCm > lineSensorPm + LS_PERIOD)
  {
    // reading left and right LS
    leftLSReading = analogRead(leftLSPin);
    rightLSReading = analogRead(rightLSPin);

    // only print out the values when we need to debug (to make serial monitor clean)
    if (LSDebug)
    {
      Serial.print("leftLS: ");
      Serial.print(leftLSReading);
      Serial.print(", rightLS: ");
      Serial.println(rightLSReading);
    }

    // reset previous millis
    lineSensorPm = lineSensorCm;
  }
  // moving robot after reading line sensor values
  // adjusting motor speed when the robot moves over the white line
  // YOU CAN WRITE YOUR CODE + USING EXISTING LIBRARY
}

/*
void lowerSpeed() {
  ml->setSpeed(slowBlock);
  mr->setSpeed(slowBlock);
}

void normalSpeed() {
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
}

// first move forward x m, turn right
void initial() {
  //hard code going forward
}

// if right is white turn right, if left is white turn left
void followLine() {
  if (leftLine == WHITE && rightLine == BLACK) mr->setSpeed(innerTurnSpeed);
  else if (leftLine == BLACK && rightLine == WHITE) ml->setSpeed(innerTurnSpeed);
  else normalSpeed();
}

// if IR sensor detect enter tunnel
void tunnelDriving() {
  if (leftUS < tunnelLeftClearance + 0.5) mr->setSpeed(innerTurnSpeed);
  else if (leftUS > tunnelLeftClearance - 0.5) ml->setSpeed(innerTurnSpeed);
  else normalSpeed();
}

*/