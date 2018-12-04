/*
2/1/15
Elt 117, HW 3
Created by: Luis Gomez
*/

int ledPin = 13;
int lightOn;
int lightOff;
int numFlash;

void setup()
{
  pinMode(ledPin,OUTPUT);
  portConfiguration(); // initiates serial connection
}

void loop()
{
  userInterface(); // Prompts & records user input for LED flash delays and number of flashes
  flashLED(lightOn,lightOff,numFlash); // Receives recorded user values and flashes LED accordingly
}

// Functions defined below

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("Pulse Generator V1.0");
   Serial.println();
}

int userInterface()
// Prompts user input for delays and number of flashes
{
  Serial.println("Expressed in milliseconds, enter time on: ");
  Serial.println();
  lightOn = inputOn();
  Serial.println();
  Serial.println("Expressed in milliseconds, enter time off: ");
  Serial.println();
  lightOff = inputOff();
  Serial.println();
  numFlash = inputFlash();
}

int inputOn()
// Prompts user for duration to flash LED ON
{
  int durationOn = 0;
  Serial.print("Time On: ");
  while(durationOn ==0)
  {
    if (Serial.available() > 0)
      {
        durationOn = Serial.parseInt(); 
        Serial.print(durationOn);
        durationOn = check(durationOn);
      }
  }
  return durationOn;
}

int inputOff()
// Prompts user for duration to flash LED OFF
{
  int durationOff = 0;
  Serial.print("Time Off: ");
  while (durationOff ==0)
  {
    if (Serial.available() > 0)
      {
        durationOff = Serial.parseInt();
        Serial.print(durationOff);
        durationOff = check(durationOff);
       }
  }
  return durationOff;
}

int inputFlash()
{
  int flashValue = 0;
  Serial.print("Number of Flashes: ");
  while (flashValue == 0)
  {
    if (Serial.available() > 0)
      {
        flashValue = Serial.parseInt();
        Serial.print(flashValue);
        flashValue = check(flashValue);
       }
  } 
  return flashValue;
}

int flashLED(int flash,int dim, int num)
// Receives user input and flashes LED accordingly
{
  for (int x = 0; x < num; x++)
  {
    Serial.println();
    digitalWrite(ledPin, HIGH);
    Serial.print("On: ");
    Serial.print(flash);
    Serial.println(" m.s.");
    delay(flash);
    digitalWrite(ledPin, LOW);
    Serial.print("Off: ");
    Serial.print(dim);
    Serial.println(" m.s.");
    delay(dim);
  }
  Serial.println();
}
  
int check(int enterednumber)
// checks if user input is an invalid value
{  
  if (enterednumber < 0 || enterednumber > 1000)
  {
    Serial.print(" is an Invalid Value, please try again.");
    Serial.println();
    return(0);
  }
  Serial.println();
  return (enterednumber);
}
