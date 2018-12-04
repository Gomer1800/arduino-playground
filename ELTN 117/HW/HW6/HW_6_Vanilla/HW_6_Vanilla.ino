/* 
HW 6
Luis Gomez
*/

int sensorValue = 0;
int outputValue = 0;
const int analogInPin = A0;
const int analogOutPin = 0;

void setup()
{
  LEDconfiguration();
}

void loop()
{
  readAnalog();
  scaleAnalog();
  displayAnalog();
}

// Setup Functions defined below

void LEDconfiguration()
{
  for(int LED = 1; LED < 6; LED++)
  {
    pinMode(LED,OUTPUT);
  }
}

// Loop functions defined below

int readAnalog()
{
  sensorValue = analogRead(analogInPin);
  return sensorValue;
}

int scaleAnalog()
{
  outputValue = map(sensorValue, 0, 1023, 0, 5); 
  return outputValue;
}

int displayAnalog()
{
  analogWrite(analogOutPin, outputValue);
  if (outputValue >0)
  {
    for(int ledPin = 1; ledPin <=outputValue; ledPin++)
    {
      digitalWrite(ledPin,HIGH);
    }
  }
  for(int ledPin = 5; ledPin > outputValue; ledPin--)
  {
    digitalWrite(ledPin,LOW);
  }
}
