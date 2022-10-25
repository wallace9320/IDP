// initialise the line sensor values
int leftLSReading = 0;
int rightLSReading = 0;
int farRightLSReading = 0;

// function for reading line sensor values and moving the robot
void setLowerSpeed() {
  if (mlSpeed != slowSpeed || mrSpeed != slowSpeed) {
    ml->setSpeed(slowSpeed);
    mr->setSpeed(slowSpeed);
    ml->run(FORWARD);
    mr->run(FORWARD);
    mlSpeed = slowSpeed;
    mrSpeed = slowSpeed;
  }
}

void setNormalSpeed() {
  if (mlSpeed != normalSpeed || mrSpeed != normalSpeed) {
    ml->setSpeed(normalSpeed);
    mr->setSpeed(normalSpeed);
    ml->run(FORWARD);
    mr->run(FORWARD);
    mlSpeed = normalSpeed;
    mrSpeed = normalSpeed;
  }
}

void turnRight() {
  if (mlSpeed != ot || mrSpeed != it) {
    ml->setSpeed(ot);
    mr->setSpeed(it);
    ml->run(FORWARD);
    mr->run(BACKWARD);
    mlSpeed = ot;
    mrSpeed = it;
  }
}

void turnLeft() {
  if (mlSpeed != it || mrSpeed != ot) {
    ml->setSpeed(it);
    mr->setSpeed(ot);
    ml->run(BACKWARD);
    mr->run(FORWARD);
    mlSpeed = it;
    mrSpeed = ot;
  }
}

void followLine() {
  leftLSReading = digitalRead(leftLSPin);
  rightLSReading = digitalRead(rightLSPin);
  farRightLSReading = digitalRead(farRightLSPin);
  if (leftLSReading == WHITE && rightLSReading == BLACK) turnLeft();
  else if (leftLSReading == BLACK && rightLSReading == WHITE && farRightLSReading == BLACK) turnRight();
  else setNormalSpeed();
}

void tunnelDriving() {
  int leftUSreading = readUSSensor(false);
  if (leftUSreading < tunnelLeftClearance + 0.5) turnLeft();
  else if (leftUSreading > tunnelLeftClearance - 0.5) turnRight();
  else setNormalSpeed();
}

/*
// timing Motor
unsigned long motorCm;
unsigned long motorPm;
const int MOTOR_PERIOD = 50; // updating motor speeds in every 50ms

debug purpose, when we change to true, it will print out values that sensor reads on serial monitor
bool LSDebug = false;
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
*/
