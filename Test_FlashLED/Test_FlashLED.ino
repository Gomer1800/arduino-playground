

int x = 1000;
int y = 2000;
int light;

void setup()
{
  pinMode(13,OUTPUT);
}

void loop()
{
 light = flashLED(x, y);
}
  
  
  
  int flashLED(int flash, int wait)
{
  digitalWrite(13, HIGH);
  delay(flash);
  digitalWrite(13, LOW);
  delay(wait);
}

