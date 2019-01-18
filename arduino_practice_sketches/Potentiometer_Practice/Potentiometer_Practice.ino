/* 
2/11/15
Luis Gomez
Practice
The program will receive potentiometer readings and will record potentiometer values when the user presses 
the button. User can define delay values for a LED.
*/

int button = 4;
int sensorValue = 0; 
int outputValue = 0;
const int analogInPin = A0; 
const int analogOutPin = 0; 
int LED;

void setup()
{
  LEDconfiguration();
  portConfiguration();
  buttonConfiguration();
}

void loop()
{
  int on = timeOn();
  int off = timeOff();
  showtime(on,off);
}

// Setup Functions defined below

void LEDconfiguration()
{
  LED = 9;  
  pinMode(LED,OUTPUT);
}

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
}

int buttonConfiguration()
// Configures switch using pin 4
{
  pinMode(button, INPUT); // configure pin 4 as input
  digitalWrite (button, HIGH); // turn on pullup resistor on pin 4
  Serial.println("Potentiometer Practice V.5");
  Serial.println();
}

// loop functions defined below

int timeOn()
{
  int delayOn = 0; 
  while (delayOn == 0)
  {
   sensorValue = analogRead(analogInPin);  
   outputValue = map(sensorValue, 0, 1023, 0, 255); 
   analogWrite(analogOutPin, outputValue);
   switchButton();
   delayOn = outputValue;
   Serial.print("Delay ON set to: ");                       
   Serial.print(sensorValue);
   Serial.println();
  }
  return delayOn;
}

int timeOff()
{
  int delayOff = 0;
  while (delayOff == 0)
  {
   sensorValue = analogRead(analogInPin);  
   outputValue = map(sensorValue, 0, 1023, 0, 255); 
   analogWrite(analogOutPin, outputValue);
   switchButton();
   delayOff = outputValue;
   Serial.print("Delay OFF set to: " );                       
   Serial.print(sensorValue);
   Serial.println();   
  }
  return delayOff;
}

int showtime(int delayOn, int delayOff)
{
  Serial.println("Press button to start to flash LED");
  switchButton();
  digitalWrite(LED,HIGH);
  delay(delayOn);
  digitalWrite(LED,LOW);
  delay(delayOff);
}

int switchButton()
{
  int clickCounter = 0;
  while (clickCounter < 1) // Acts as a counter, limits the number of times the button can be pressed to one
  {
    int value = digitalRead (button);
    while (value == 1) // waits for the user to press the button, a 0 would be an off state
    {
      value = digitalRead (button); // when the button is pressed, the potentiometer value is recorded
    }
    delay(50);
    clickCounter++;
  }
}
