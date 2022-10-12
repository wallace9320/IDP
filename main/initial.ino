// move forward 20 cm and turn right
// time estimated for now, need to test and put the right time values
void initial()
{
    if (millis() - buttonTime < 3000)
    {
        normalSpeed();
    }
    if (millis() - buttonTime < 5000)
    {
        // turn right
    }
}