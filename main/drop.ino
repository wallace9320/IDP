void actualDropping() {
  lservo.write(15.0/270*180);
  rservo.write(135.0/270*180);
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
  delay(straightTime);

  mr->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  delay(turnTime);

  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);

  holding = false;
}