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
  portConfiguration();
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
  for(int LED = 1; LED < 5; LED++)
  {
    pinMode(LED,OUTPUT);
  }
}

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
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
  Serial.println(outputValue);
  return outputValue;
}

int displayAnalog()
{
  analogWrite(analogOutPin, outputValue);
  Serial.println(outputValue);
 if(outputValue <= 5)
 {
   digitalWrite(outputValue,HIGH);
 }
 else
 {
   digitalWrite(outputValue,LOW);
 }
}
