// Line follower
// TODO - 1. read line sensor
//      - 2. set motors based on line sensor readings

// timing LS - better way than using delay function
unsigned long lineSensorCm; // line sensor current millis
unsigned long lineSensorPm; // line sensor previous millis
const int LS_PERIOD = 50;   // checking line sensor value in every 50 ms

// // timing Motor
// unsigned long motorCm;
// unsigned long motorPm;
// const int MOTOR_PERIOD = 50; // updating motor speeds in every 50ms

// debug purpose, when we change to true, it will print out values that sensor reads on serial monitor
bool LSDebug = false;

// initialise the line sensor values
int leftLSReading = 0;
int rightLSReading = 0;

// function for reading line sensor values and moving the robot
void setForward() {
  m1->run(FORWARD);
  m2->run(FORWARD);
}

void setLowerSpeed() {
  ml->setSpeed(slowSpeed);
  mr->setSpeed(slowSpeed);
}

void setNormalSpeed() {
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
}

void followLine()
{
  // to avoid using delay() -> reading line sensor values in every LS_PERIOD
  lineSensorCm = millis();
  if (lineSensorCm > lineSensorPm + LS_PERIOD)
  {
    // reading left and right LS
    // Need to change this part
    leftLSReading = digitalRead(leftLSPin);
    rightLSReading = digitalRead(rightLSPin);

    // only print out the values when we need to debug (to make serial monitor clean)
    if (LSDebug)
    {
      Serial.print("leftLS: ");
      Serial.print(leftLSReading);
      Serial.print(", rightLS: ");
      Serial.println(rightLSReading);
    }

    if (leftLSReading == WHITE && rightLSReading == BLACK) mr->setSpeed(innerTurnSpeed);
    else if (leftLSReading == BLACK && rightLSReading == WHITE) ml->setSpeed(innerTurnSpeed);
    else setNormalSpeed();
    // reset previous millis
    lineSensorPm = lineSensorCm;
  }
  // moving robot after reading line sensor values
  // adjusting motor speed when the robot moves over the white line
  // YOU CAN WRITE YOUR CODE + USING EXISTING LIBRARY
}

// if IR sensor detect enter tunnel
void tunnelDriving() {
  int leftUSreading = leftUS.reading(readUSSensor(false));
  if (leftUSreading < tunnelLeftClearance + 0.5) mr->setSpeed(innerTurnSpeed);
  else if (leftUSreading > tunnelLeftClearance - 0.5) ml->setSpeed(innerTurnSpeed);
  else setNormalSpeed();
}

/*

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