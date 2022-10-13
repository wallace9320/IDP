void droppingMovement() {
  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(turnTime);
  
  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);
  delay(striaghtTime);

  //dropping sequence

  ml->run(BACKWARD);
  mr->run(BACKWARD);
  delay(striaghtTime);

  mr->setSpeed(innerTurnSpeed);
  mr->run(FORWARD);
  delay(turnTime);

  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);

  holding = false;
}