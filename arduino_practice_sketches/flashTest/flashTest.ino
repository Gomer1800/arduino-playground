/*
1/28/15
flashTest
*/
int flashes = 1;
int waitTime = 1000;
int ledPin = 13;

void setup()
{
  pinMode (ledPin, OUTPUT); // setup
}

void loop()
{
  flashSet (waitTime, flashes);
  delay(1000);
}

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
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
}
