// move forward 20 cm and turn right
// time estimated for now, need to test and put the right time values
void initialMovement()
{
  ml->setSpeed(normalSpeed);
  mr->setSpeed(normalSpeed);
  ml->run(FORWARD);
  mr->run(FORWARD);
  delay(2000);

  mr->setSpeed(innerTurnSpeed);
  mr->run(BACKWARD);
  delay(turnTime);

  mr->setSpeed(normalSpeed);
  mr->run(FORWARD);

  start = false;
}