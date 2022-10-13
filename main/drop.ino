void droppingMovement() {
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(2000);
  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(2000);
  //dropping sequence
  ml->run(BACKWARD);
  mr->run(BACKWARD);
  delay(2000);
  mr->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  delay(2000);
  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);
  mr->run(FORWARD);
  holding = false;
}