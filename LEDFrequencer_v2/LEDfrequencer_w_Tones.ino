/*
Created by: Luis Gomez
*/

int lightshowNum;
int flashNum;
unsigned int noteIndex = 0;
unsigned int delayIndex = 0;
int button = 12; // variable "button" defined as 12
unsigned int drunkenSailor[36] = {440, 440, 440, 440, 440, 440, 440, 294, 349, 440, 
                                  392, 392, 392, 392, 392, 392, 392, 261, 330, 392, 
                                  440, 440, 440,440, 440, 440, 440, 494, 261, 294, 
                                  261, 440, 392, 330, 294, 294};
unsigned int sailorDelay[36] = {300, 150, 150, 300, 150, 150,300,300,300,300,
                                300, 150, 150,300,150,150,300,300,300,300,
                                300,150,150,300,150,150,300,300,300,300,
                                300,300,300,300,500,500};
                              
unsigned int mario[24] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,
                          660,760,860,700,760,660,520,580,480};
unsigned int marioDelays[24] = {150,300,300,100,300,550,575,450,400,500,300,330,150,
                                300,200,200,150,300,150,350,300,150,150,500};
                    
void setup()
{
   LEDconfiguration(); // Configures pins 2-6 as outputs for LEDS
   portConfiguration(); // initiates serial connection 
   buttonConfiguration(); // configures pin 12 as an input and turns on the switch
}

void loop()
{
  userInterface(); // Prompts & records user input for LED flash delays and number of flashes
  sequencerConfiguration(lightshowNum, flashNum); // Receives recorded user values and flashes LED accordingly
}

// Setup Functions defined below

void LEDconfiguration()
{
  for (int a = 2; a < 7; a++) // sets up pins 2-6 as Outputs
  {
    pinMode(a,OUTPUT);
  }
}

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("LED Frequencer V2.0");
   Serial.println();
}

void buttonConfiguration()
// Configures switch using pin 12
{
  pinMode(button, INPUT); // configure pin 12 as input
  digitalWrite (button, HIGH); // turn on pullup resistor on pin 12
}

// Loop functions defined below

int userInterface()
{
  Serial.println("Which lightshow would you like to see?");
  Serial.println();
  lightshowNum = showSelection(); // Prompts user for light show number and sets user input as a global variable
  Serial.println();
  flashNum = inputFlash(); // Prompts user for number of times to display lightshow and sets user input as a global variable
}

int showSelection()
{
  int input = 0; // acts as a counter, only a valid user-defined input will override its current value
  Serial.print("Sequence Chosen: ");
  while(input ==0)
  {
    if (Serial.available() > 0) // awaits user input
      {
        input = Serial.parseInt(); 
        Serial.print(input);
        input = checkSequence(input); // checks if user input is a valid value between 1-3
      }
  }
  return input;
}

int inputFlash()
{
  int flashValue = 0; // acts as a counter
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
  noteIndex = 0;
  delayIndex = 0;
  Serial.println("Press button to initiate start sequence");
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
    if (showSelection == 1) // Turns LEDS(pins 2-6) on in sequence and then turns them off in reverse order
    {
      while (ledPin < 7)
        {
          if(noteIndex >= 24){
            noteIndex = 0;
            delayIndex = 0;
          }
          digitalWrite(ledPin, HIGH);
          tone(7, mario[noteIndex]);
          delay(marioDelays[delayIndex]);
          noTone(7);
          ledPin++;
          noteIndex++;
          delayIndex++;
        }
      while (ledPin > 1)
        {
          if(noteIndex >= 24){
            noteIndex = 0;
            delayIndex = 0;
          }
          digitalWrite(ledPin,LOW);
          tone(7, mario[noteIndex]);
          delay(marioDelays[delayIndex]);
          noTone(7);
          ledPin--;
          noteIndex++;
          delayIndex++;
        }
    }
    if (showSelection == 2) // Flashes LEDS(pins 2-6) on/off in sequence and then flashes them on/off in reverse order
    {
      while (ledPin < 7)
         {
           if(noteIndex >= 35){
            noteIndex = 0;
            delayIndex = 0;
           }
           digitalWrite(ledPin, HIGH);
           tone(7,drunkenSailor[noteIndex]);
           delay(sailorDelay[delayIndex]);
           noTone(7);
           digitalWrite(ledPin,LOW);
           delay(150);
           ledPin++;
           noteIndex++;
           delayIndex++;
         }
      ledPin--;
      while (ledPin > 1)
        {
          if(noteIndex >= 35){
            noteIndex = 0;
            delayIndex = 0;
          }
          digitalWrite(ledPin,LOW);
          tone(7,drunkenSailor[noteIndex]);
          delay(sailorDelay[delayIndex]);
          noTone(7);
          ledPin--;
          noteIndex++;
          delayIndex++;
          digitalWrite(ledPin, HIGH);
          delay(sailorDelay[delayIndex]);
        }
    }
    if (showSelection == 3) // Flashes LEDS on/off in order from outer to inner, and then in reverse
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
// checks if user input is an invalid value outside of the range 1-3
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
// checks if user input is an invalid value less than or equal to zero
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

int startSwitch()
{
  int counter = 0;
  while (counter < 1) // acts as a counter, waiting for the user to successfully press the button once
  {
    int value = digitalRead (button);
    while (value == 1)
    {
      value = digitalRead (button);
    }
    delay(10);
    counter++;
  }
}
