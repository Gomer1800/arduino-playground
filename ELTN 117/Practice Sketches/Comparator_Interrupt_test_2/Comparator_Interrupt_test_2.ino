void setup()
{ 
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  attachInterrupt(0, LEDtrigger, RISING);
}

void loop()
{
  char input = readSerial();
  triggerTest(input);
}

char readSerial()
{
  char serialInput;
  if(Serial.available() >0)
  {
    serialInput = Serial.read();
    Serial.println(serialInput);
  }
  return serialInput;
}

int triggerTest(char x)
{
  switch(x)
  {
  case '1':
    digitalWrite(2,HIGH);
    break;
  case '2':
    digitalWrite(2,LOW);
    break;
  default:
    return x;
    break;
  }
}

void LEDtrigger()
{
  Serial.println("Mike, do you even lift bro?");
  digitalWrite(2,LOW);
}



