/*
Program 3
Luis Gomez
*/

int ledPin = 4;
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
  flashLED(numFlash); // Receives recorded user values and flashes LED accordingly
}

// Functions defined below

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("LED Flashing program written by Luis Gomez");
   Serial.println();
}

int userInterface()
// Prompts user input for delays and number of flashes
{
  numFlash = inputFlash();
}

int inputFlash()
{
  int flashValue = 0;
  Serial.print("Enter the number of Flashes: ");
  while (flashValue == 0)
  {
    if (Serial.available() > 0)
      {
        flashValue = Serial.parseInt();
        Serial.print(flashValue);
        flashValue = check(flashValue);
        Serial.println();
       }
  } 
  return flashValue;
}

int flashLED(int num)
// Receives user input and flashes LED accordingly
{
  for (int x = 1; x <= num; x++)
  {
    Serial.print(x);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
    Serial.println();
  }
  Serial.println();
}
  
int check(int enterednumber)
// checks if user input is an invalid value
{  
  if (enterednumber <= 0 )
  {
    Serial.print(" is an Invalid Value, please try again.");
    Serial.println();
    return(0);
  }
  Serial.println();
  return (enterednumber);
}
