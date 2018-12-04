/*
Name of program: HW_2
Purpose of program: Flash LED
Created by: Luis Gomez
Date: 1/21/15

--------------------------------

Alternates between flashing LED 10 times at 100 ms & flashing LED 5 times at 
250 ms, forever.
Hardware used: No external wiring, uses LED on board (pin #13)
*/

// Variable definition

int LEDPin = 13;
int fastBlink = 100; //100 millisecond delay
int slowBlink = 250; // 250 millisecond delay
int pause = 2000; // 2 second pause
int numFlashes = 0;

void setup()    //Configure I/O
{
pinMode (LEDPin, OUTPUT);
}

void loop()
{
  while(numFlashes < 10) // Flash LED 10 times at 100 m.s.
  {
  digitalWrite (LEDPin, HIGH);
  delay (fastBlink);
  digitalWrite (LEDPin, LOW);
  delay (fastBlink);
  numFlashes++; // Increase numFlashes variable by 1
}
  delay (pause); // Turn off LED for 2 seconds
  
  while (numFlashes < 15) // Flash LED 5 times at 250 m.s.
  {
  digitalWrite (LEDPin, HIGH);
  delay (slowBlink);
  digitalWrite (LEDPin, LOW);
  delay (slowBlink);
  numFlashes++;
  }
 numFlashes = 0;
 delay (pause); // Turn off LED for 2 seconds
}
