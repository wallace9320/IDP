#include "constant.h"
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
// #include <SharpIR.h>

#include "utility/Adafruit_MS_PWMServoDriver.h"

bool found = false;
Servo lservo;
Servo rservo;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *ml = AFMS.getMotor(1);
Adafruit_DCMotor *mr = AFMS.getMotor(2);

// SharpIR leftIRSensor = SharpIR(leftIRPin, 1080);

// process value from US sensor
int readUSSensor(bool front = true)
{
  int trigPin = front ? frontUStrigPin : leftUStrigPin;
  int echoPin = front ? frontUSechoPin : leftUSechoPin;
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) * 0.034 / 2;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  ml->setSpeed(0);
  mr->setSpeed(0);
  ml->run(FORWARD);
  mr->run(FORWARD);

  lservo.attach(lservoPin);
  rservo.attach(rservoPin);
  lservo.write(150.0/270*180);
  rservo.write(0.0/270*180);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(leftLSPin, INPUT);
  pinMode(rightLSPin, INPUT);
  pinMode(farRightLSPin, INPUT);
  pinMode(frontUStrigPin, OUTPUT);
  pinMode(frontUSechoPin, INPUT);
  pinMode(leftUStrigPin, OUTPUT);
  pinMode(leftUSechoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(hallEffectPin, INPUT);
  pinMode(leftIRPin, INPUT);
  pinMode(runningLED, OUTPUT);  

  timeButton = millis();
  timeLED = millis();

  delay(1000);
}

void loop() {
  if (digitalRead(buttonPin) == LOW && millis() - timeButton > 1000)
  {
    button = !button;
    timeButton = millis();
    ml->setSpeed(255);
    mr->setSpeed(255);
  }
  if (button) {
    if (digitalRead(farRightLSPin) == WHITE) {
    delay(1000);
    mr->setSpeed(innerTurnSpeed);
    mr->run(BACKWARD);
    delay(500);
    while (digitalRead(leftLSPin) == BLACK) continue;
    delay(250);
    mr->setSpeed(normalSpeed);
    mr->run(FORWARD);
    delay(1500);
    while (readUSSensor(true) > 4) continue;
    ml->setSpeed(0);
    mr->setSpeed(0);
    }

    // frontUS = readUSSensor(true);
    // leftUS = readUSSensor(false);
    // leftIR = analogRead(leftIRPin);
    // Serial.print("     ");
    // Serial.print(frontUS);
    // Serial.print("     ");
    // Serial.print(leftUS);
    // Serial.print("     ");
    // Serial.println(leftIR);
    // i++;
    // if (!found && leftIR > 200) {
    //   ml->setSpeed(innerTurnSpeed);
    //   ml->run(BACKWARD);
    //   // while (readUSSensor(true) > 30){
    //   //   Serial.println(readUSSensor(true));
    //   // }
    //   while (analogRead(frontIRPin) < 200) continue;
    //   ml->setSpeed(normalSpeed);
    //   ml->run(FORWARD);
    //   found = true;
    // }
    // if ((frontUS < 4 || frontUS > 2000 && millis() - timeHard > 15000) && !holding) {
    //   Serial.println("set zero");
    //   ml->setSpeed(0);
    //   mr->setSpeed(0);
    //   delay(3000);
    // }
  }

}
