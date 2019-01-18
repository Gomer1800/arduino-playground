// Uses switch to sequence LED's
//T Thoen 2-9-15
// Uses pins 2 -6 for LED's
// Uses pin 12 for the switch

int button = 12; // variable "button" defined as 12
int counter = 2;
int value = 0;

void setup()
{
  pinMode (button, INPUT); // configure pin 12 as input
  digitalWrite (button, HIGH); // turn on pullup resistor on pin 12
  
  for (int a = 0; a <8; a++) // configure pins 0-7 as outputs
  {
    pinMode(a, OUTPUT);
  }
}

void loop()
{
  while (counter < 8)
  {
    value = digitalRead (button);
    while (value == 1)
    {
      value = digitalRead (button);
    }
    digitalWrite(counter, HIGH);
    delay(10);
    counter++;
  }
  while (counter > 1)
  { 
    counter--;
    value = digitalRead (button);
    while (value == 1)
      {
        value = digitalRead (button);
       }
    digitalWrite (counter, LOW);
    delay(10);
  }
}
  

