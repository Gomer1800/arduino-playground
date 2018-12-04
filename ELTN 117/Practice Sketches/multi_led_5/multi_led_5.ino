// Sequences 5 LED's
//Connect to pin 0 to 4
// T. Thoen
//2/4/15

void setup()
{
  for (int a =2; a < 7; a++)
  {
    pinMode(a,OUTPUT);
  }
}

void loop()
{
  for (int a = 2; a <7; a++)
  {
  digitalWrite(a, HIGH);
  delay(250);
  }
  for (int a= 2; a <7; a++)
  {
    digitalWrite(a,LOW);
    delay(250);
  }
}
