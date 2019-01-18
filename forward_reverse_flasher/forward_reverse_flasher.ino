/* This program flashes LEDS in a forward and reverse order depending on whether
 *  one of two buttons is pressed. By default buttons 10 & 11
 *  
 *  Luis Gomez 2015
 */

int button1 = 10;
int button2 = 11;
int LEDpin;

void setup()
{
   LEDconfiguration();
   portConfiguration();
   buttonConfiguration();
}

void loop()
{
 phase1(); // Flashes LEDs in sequence from pins 3 to 7 while button 1 is pressed
 phase2(); // Flashes LEDs in sequence from pins 7 to 3 while button 2 is pressed
}

// Setup Functions defined below

void LEDconfiguration()
{
  for (int a = 3; a < 8; a++)
  {
    pinMode(a,OUTPUT);
  }
}

void portConfiguration() // Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("LED Frequencer V1.0");
   Serial.println();
}

void buttonConfiguration()
{
  pinMode(button1, INPUT);
  digitalWrite(button1, HIGH);
  pinMode(button2, INPUT);
  digitalWrite(button2, HIGH);
}

// Loop functions defined below

int phase1()
{
  LEDpin = 3;
  while (LEDpin < 8)
        {
          int value = 1;
          while (value == 1) // waits for user to press button, doing so will change the value to 0
          {
            value = digitalRead (button1); 
          }
          delay(10);
          digitalWrite(LEDpin, HIGH); // flashes LED
          delay(35);
          while (value == 1) // waits for user to press button again
          {
            value = digitalRead (button1);
          }
          delay(10);
          digitalWrite(LEDpin, LOW); // dims LED
          delay(35);
          LEDpin++;
        }
        
}

int phase2() // Same as Phase 1 except this flashes LEDS in reverse order while contingent on the pressing of button 2 
{
  LEDpin = 7;
  while (LEDpin > 2)
        {
          int value = 1;
          while (value == 1)
          {
            value = digitalRead (button2);
          }
          delay(10);
          digitalWrite(LEDpin, HIGH);
          delay(35);
          while (value == 1)
          {
            value = digitalRead (button2);
          }
          delay(10);
          digitalWrite(LEDpin, LOW);
          delay(35);
          LEDpin--;
        }
}
