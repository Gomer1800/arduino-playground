#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char input;
int delayNote = 500;

void setup()
{
  portConfiguration();
}

void loop()
{
  userInterface();
  LCDdisplay();
  playMusic();
  Serial.println("Bravo!");
  Serial.println();
}

void portConfiguration() // Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("TONE Generator V1.0");
   Serial.println();
}

int userInterface()
{
  Serial.println("What note would you like to hear?");
  Serial.println("You can select C,D,E,F,G,A, or B");
  Serial.println();
  noteSelection();
}

int noteSelection()
{
  int count =0;
  while(count ==0)
  {
   if (Serial.available() > 0)
      {
        input = Serial.read(); 
        Serial.print(input);
        Serial.println();
        switch(input)
        {
          case 'C':
          return (input);
          break;
          case 'D':
          return (input);
          break ;
          case 'E':
          return (input);
          break;
          case 'F':
          return (input);
          break;
          case 'G':
          return (input);
          case 'A':
          return (input);
          break;
          case 'B':
          return (input);
          break;
          case 'X':
          return (input);
          break;
          case 'Y':
          return (input);
          break;
          default:
          Serial.println("I'm sorry that's not allowed, please choose a valid note");
          break;
        }
      }
   }
}

int LCDdisplay()
{
  for(int count = 0;count< 1; count++)
  {
    lcd.begin(16, 2);
    lcd.println("Note ");
    lcd.print(input);
  }
}

int playMusic()
{
  for(int count= 0;count< 1; count++)
  {
    switch(input)
    {
      case 'C':
      tone(7, 261, delayNote);
      break;
      case 'D':
      tone(7, 294, delayNote);
      break;
      case 'E':
      tone(7, 330, delayNote);
      break; 
      case 'F':
      tone(7, 349, delayNote);
      break; 
      case 'G':
      tone(7, 392, delayNote);
      break;
      case 'A':
      tone(7, 440, delayNote);
      break;
      case 'B':
      tone(7, 494, delayNote);
      break;
      case 'X':
      tone(7, 523, delayNote);
      break;
      case 'Y':
      tone(7, 587, delayNote);
      break;
      
    }
  }
}
