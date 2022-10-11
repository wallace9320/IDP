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
  // white: < threshold
  // black: > threshold  * should as elec team about what values black and white colour get
  // right = black and left = black
  if (leftLSReading > LS_THRESHOLD && rightLSReading > LS_THRESHOLD)
  {
    // move forwards
    robot.moveForward();
  } // right = black and left = white
  elif (leftLSReading > LS_THRESHOLD && rightLSReading < LS_THRESHOLD)
  {
    // turn left
    robot.turnLeft();
  } // right = white and left = black
  elif (leftLSReading < LS_THRESHOLD && rightLSReading > LS_THRESHOLD)
  {
    // turn right
    robot.turnRight();
  }
  else
  {
    // stop
    robot.stop();
  }
}

// setting motor speeds and direction
// all the possible movement functions will place here
class setMotors
{

private: // can only change this value inside this class, cannot be modified outside
  float MOTOR_BASE_SPEED = 300.0;
  float MOTOR_MIN_SPEED = 20.0; // when we move over the ramp, it needs to be greater than min speed
                                // otherwise it will move backwards
public:
  float motorLeftSpeed;
  float motorRightSpeed;

  void moveForward()
  { // update motor speed in every MOTOR_PERIOD
    motorCm = millis();
    if (motorCm > motorPm + MOTOR_PERIOD)
    {
      // will create motorLeft and motorRight object
      motorLeft.setSpeed(MOTOR_BASE_SPEED);
      motorRight.setSpeed(MOTOR_BASE_SPEED);

      // debug
      printSpeed();

      // reset motor previous millis
      motorPm = motorCm;
    };
  }
  // will code later but similar to moveForward function above.
  void turnRight(){
      // check motor speed and wheels' movement and set appropriate speed values to turn robot in desired angle
  };
  void turnLeft();
  void moveBackward();
  void stop()
  {
    motorLeft.setSpeed(0);
    motorRight.setSpeed(0);
  }
  // only print out left and right speed when MotorDebug = true.
  void printSpeed()
  {
    if (MotorDebug)
    {
      Serial.print("Left speed: ");
      Serial.print(motorLeftSpeed);
      Serial.print(", Right speed: ");
      Serial.println(motorRightSpeed);
    }
  }
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