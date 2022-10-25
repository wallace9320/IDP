void actualDropping() {
  lservo.write(135.0/270*180);
  rservo.write(15.0/270*180);
  delay(300);
}

void droppingMovement() {
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(turnTime);

  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(straightTime);

  actualDropping();

  ml->run(BACKWARD);
  mr->run(BACKWARD);
  delay(straightTime+700); //1000

  mr->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  delay(turnTime+100); //300

  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);

  holding = false;
  noOfWhiteLines = 0;
  turn = false;
}