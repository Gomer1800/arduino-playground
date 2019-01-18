int flashNum = 0; // user defined variable for number of LED flashes
int delayLED = 100; // Delay for LED flashes, starts at 100 m/s and then increments in loop by 100
int pinLED = 13; // pin 13 is the built in LED on the Arduino
int speakerPin = 3; // configures a digital pin for use with a small speaker

void setup()
{
Serial.begin(9600); // inititates Serial Monitor at 9600 BAUD
pinMode(pinLED, OUTPUT); // configures the built in LED on pin 13 as an output
pinMode(speakerPin,OUTPUT); //Configures pin 3 as an output for the small speaker
}

void loop()
{
flashNum = userInterface(); // Prompts user for number of flashes
lightShow(flashNum); // passes value of flashNum, and flashes LEDS accordingly
crescendo(); // Beeps noise, resets flashNum, and ends loop with ALL DONE
}

int userInterface()
{
  Serial.println("Hello, how many times would you like the LEDs to flash?");
  Serial.print("Number of flashes: ");
  int userInput =0; // defines user variable as an integer value
  while(userInput <=0) // Waits for user to submit a value greater than 0
  {
    if (Serial.available() > 0)
    {
      userInput = Serial.parseInt(); // converts user input into an integer
      Serial.println(userInput);
    }
  }
  return userInput;// passes value back to main loop, where is it used in lightshow()
}

int lightShow(int userInput) //declares the user defined value as an integer to be used in this function
{
  for(int count = 0; count< userInput; count++) // Flashes the LEDs a number of times equal to the user defined value of flashNum, which is now userInput 
  {
  digitalWrite(pinLED, HIGH); // LED is on
  delay(delayLED); 
  digitalWrite(pinLED,LOW); //LED is off
  delay(delayLED);
  delayLED = delayLED + 100; // increments delay by 100 m/s for next loop
  }
}

int crescendo() // Emits beep for 3 seconds, then makes final prompt and resets flashNum
{
  digitalWrite(speakerPin, HIGH); // Beeps speaker 
  delay(3000); // 3 second delay, speaker is still ON
  digitalWrite(speakerPin, LOW);// turns speaker OFF
  flashNum = 0; // resets value so loop can run again
  Serial.println("ALL DONE"); // C'est Finis
}
