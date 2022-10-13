void actualDropping() {
  //dropping sequence

}

void droppingMovement() {
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(turnTime);

  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(straightTime);

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