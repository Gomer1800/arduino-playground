/*
2/1/15
Elt 117, HW 3
Created by: Luis Gomez
*/

int ledPin = 13;

void setup()
{
  pinMode(ledPin, OUTPUT);
  portConfiguration();
}

void loop()
{
  userInterface();
}

// Functions defined below

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("Pulse Generator V1.0");
}

int userInterface()
// Calls functions relying on user input
{
}


  


