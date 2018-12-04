/* 
Program 1
Luis Gomez
*/

void setup()
{
  pinMode(4,OUTPUT);
}

void loop()
{
  flashFive();
  flashForever();
}

int flashFive()
{
  int functionCount = 0;
  while(functionCount < 5)
  {
    digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
    delay(500);
    functionCount++;
  }
}

int flashForever()
{
  int forever = 0;
  while (forever ==0)
  {
    digitalWrite(4,HIGH);
  }
}

