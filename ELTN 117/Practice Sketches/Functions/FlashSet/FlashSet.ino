/*
1/28/15
Function: flashfast50
*/
int flashes = 5;
int waitTime = 100;
int ledPin = 13;

void setup()
{
  pinMode (ledPin, OUTPUT);
}

void loop()

// Function flashSet- is passed values for number of flashes and delay time
// Also calls flashFast50

void flashSet(int delTime, int numFlashes)
{
    for (int y =0; y < numFlashes; y++)
    {
      flashFast50();
      delay(delTime);
    }
}

void flashFast50()
{
  for (int x  =0; x < 5; x++)
  {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
}
