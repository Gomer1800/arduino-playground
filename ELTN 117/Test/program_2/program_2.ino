/*
Program 2
Luis Gomez
*/

int button =2;
int delaySwitch = 250;
int delayDefault = 500;
int value =0;

void setup()
{
  pinMode(4,OUTPUT);
  buttonConfiguration();
}

void loop()
{
  value = digitalRead(button);
  while (value == 1)
  {
    digitalWrite(4,HIGH);
    delay(delayDefault);
    digitalWrite(4,LOW);
    delay(delayDefault);
    value = digitalRead(button);
  }
  digitalWrite(4,HIGH);
  delay(delaySwitch);
  digitalWrite(4,LOW);
  delay(delaySwitch);
}

// setup function defined below

void buttonConfiguration()
// Configures switch using pin 2
{
  pinMode(button, INPUT); // configure pin 2 as input
  digitalWrite (button, HIGH); // turn on pullup resistor on pin 2
}


