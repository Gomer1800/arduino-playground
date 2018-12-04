/*
2/9/15
Elt 117, HW 4
Created by: Luis Gomez
*/

int lightshowNum;
int flashNum;

void setup()
{
   LEDconfiguration();
   portConfiguration(); // initiates serial connection 
   buttonConfiguration();
}

void loop()
{
  userInterface(); // Prompts & records user input for LED flash delays and number of flashes
  sequencerConfiguration(lightshowNum, flashNum); // Receives recorded user values and flashes LED accordingly
}

// Functions defined below

void LEDconfiguration()
{
  for (int a = 2; a < 7; a++)
  {
    pinMode(a,OUTPUT);
  }
}

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("LED Frequencer V1.5");
   Serial.println();
}

int buttonConfiguration();
{
  int button = 12; // variable "button" defined as 12
  pinMode (button, INPUT); // configure pin 12 as input
  digitalWrite (button, HIGH); // turn on pullup resistor on pin 12
  
  for (int a = 0; a <8; a++) // configure pins 0-7 as outputs
  {
    pinMode(a, OUTPUT);
  }
}

int userInterface()
{
  Serial.println("Which lightshow would you like to see?");
  Serial.println();
  lightshowNum = showSelection();
  Serial.println();
  flashNum = inputFlash();
}

int showSelection()
{
  int input = 0;
  Serial.print("Sequence Chosen: ");
  while(input ==0)
  {
    if (Serial.available() > 0)
      {
        input = Serial.parseInt(); 
        Serial.print(input);
        input = checkSequence(input);
      }
  }
  return input;
}

int inputFlash()
{
  int flashValue = 0;
  Serial.print("How many times would you like to see the show today: ");
  while (flashValue == 0)
  {
    if (Serial.available() > 0)
      {
        flashValue = Serial.parseInt();
        Serial.print(flashValue);
        flashValue = checkFlash(flashValue);
        Serial.println();
       }
  } 
  return flashValue;
}

int sequencerConfiguration(int showSelection, int inputNum)
// Receives user input and flashes LED accordingly
{
  int ledPin = 2;
  startSwitch();
  Serial.println();
  Serial.print("Show Starts in 3...");
  delay(1000);
  Serial.print("2...");
  delay(1000);
  Serial.print("1...");
  delay(1000);
  Serial.println("Enjoy!");
  Serial.println();
  delay(250);
  
  for (int count= 0;count < inputNum; count++)
  {
    if (showSelection == 1)
    {
      while (ledPin < 7)
        {
          digitalWrite(ledPin, HIGH);
          delay(250);
          ledPin++;
        }
      while (ledPin > 1)
        {
          digitalWrite(ledPin,LOW);
          delay(250);
          ledPin--;
        }
    }
    if (showSelection == 2)
    {
      while (ledPin < 7)
         {
           digitalWrite(ledPin, HIGH);
           delay(250);
           digitalWrite(ledPin,LOW);
           delay(250);
           ledPin++;
         }
      ledPin--;
      while (ledPin > 1)
        {
          digitalWrite(ledPin,LOW);
          delay(250);
          ledPin--;
          digitalWrite(ledPin, HIGH);
          delay(250);
        }
    }
    if (showSelection == 3)
    {
          digitalWrite(ledPin = 2,HIGH);
          digitalWrite(ledPin = 6, HIGH);
          delay(250);
          digitalWrite(ledPin = 2, LOW);
          digitalWrite(ledPin = 6, LOW);
          delay(250);
          digitalWrite(ledPin = 3, HIGH);
          digitalWrite(ledPin = 5, HIGH);
          delay(250);
          digitalWrite(ledPin = 3, LOW);
          digitalWrite(ledPin = 5, LOW);
          delay(250);
          digitalWrite(ledPin = 4, HIGH);
          delay(250);
          digitalWrite(ledPin = 4, LOW);
          delay(250);
          digitalWrite(ledPin = 3, HIGH);
          digitalWrite(ledPin = 5, HIGH);
          delay(250);
          digitalWrite(ledPin = 3, LOW);
          digitalWrite(ledPin = 5, LOW);
          delay(250);
          digitalWrite(ledPin = 2, HIGH);
          digitalWrite(ledPin = 6, HIGH);
          delay(250);
          digitalWrite(ledPin = 2, LOW);
          digitalWrite(ledPin = 6, LOW);
          delay(250);
      }
  }
}
  
int checkSequence(int enterednumber)
// checks if user input is an invalid value
{  
  if (enterednumber <= 0 || enterednumber > 3 )
  {
    Serial.print(" is an Invalid Value, please try again.");
    Serial.println();
    return(0);
  }
  Serial.println();
  return (enterednumber);
}

int checkFlash(int enterednumber)
// checks if user input is an invalid value
{  
  if (enterednumber <= 0)
  {
    Serial.print(" is an Invalid Value, please try again.");
    Serial.println();
    return(0);
  }
  Serial.println();
  return (enterednumber);
}

int  startSwitch();
{
  while (counter == 0)
  {
    value = digitalRead (button);
    while (value == 1)
    {
      value = digitalRead (button);
    }
    digitalWrite(counter, HIGH);
    delay(10);
    counter++;
  }
  while (counter > 1)
  { 
    counter--;
    value = digitalRead (button);
    while (value == 1)
      {
        value = digitalRead (button);
       }
    digitalWrite (counter, LOW);
    delay(10);
  }
}
