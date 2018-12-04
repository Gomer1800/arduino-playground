
int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  int on = 1000;
  int off = 2000;
  flashLED(on,off);
}

int flashLED(int flash, int dim)
{
  for (int x = 0; x<10; x++);
    {
      digitalWrite(ledPin, HIGH);
      Serial.print(flash);
      Serial.println("m.s.");
      delay(flash);
      digitalWrite(ledPin, LOW);
      Serial.print(dim);
      Serial.println("m.s.");
      delay(dim);
    }
}
