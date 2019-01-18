
/*#include <SoftwareSerial.h>
 SoftwareSerial mySerial(12, 13); // RX, TX
 */

// Setup Variables
int rightOut = 6;  // Use output Pin 5 for PWM
int leftOut= 5;    // Use output Pin 6 for PWM
const int leftForward = 11; //LF
const int leftReverse = 10; // LR

const int rightReverse= 3; // RR
const int rightForward = 9; // RF

volatile int lwheelPulse = 0;
volatile int rwheelPulse = 0;
int LWsensor;
int RWsensor;

int volume =100;
int audioPin =7;

// User defined values in moveRobo function
char directionUser;
int durationUser;

int speed = 255;
int speedUp;
int slowDown;
/*
int leftSpeed = 128;	// Move at medium speed
 int rightSpeed = 128;	// same for right motor	
 */

void setup() 
{
  portConfiguration(); 
  hBridgeSetUp();
  interruptSetUp();
  
}

void portConfiguration()    // setup functions
{
  Serial.begin(9600);
}

void hBridgeSetUp() // initialize digital I/O
{
  pinMode(rightForward, OUTPUT); 
  pinMode(rightReverse, OUTPUT);
  pinMode(leftForward, OUTPUT); 
  pinMode(leftReverse, OUTPUT);
}

void interruptSetUp()
{
  attachInterrupt(0, lwheelSensor, FALLING);
  attachInterrupt(1, rwheelSensor, FALLING);
}

void loop() 
{
  userInterface();
  moveRobo(directionUser);
  // Moves robot according to user defined directional & duration values
  slowMo(); 
  // Slows down robot
}

int userInterface()    // loop functions
{
  /*
  char 'W' = 'Forward';
   char 'A' = 'Left';
   char 'D' = 'Right';
   char 'S' = 'Reverse';
   */
  Serial.println("Awaiting your command pilot");
  Serial.println("You can select W(forward), A(left), D(right), or S(reverse)");
  Serial.println();
  directionCommand();
  Serial.println("For how many seconds would you like the robot to move pilot?");
  moveDuration();
}

char directionCommand()
{
  int count = 'X';
  while(count == 'X')
  {
    if (Serial.available() > 0)
    {
      directionUser = Serial.read(); 
      Serial.println(directionUser);
      count = checkMove(directionUser);
    }
  }
}

char checkMove(char enteredMove)
// Checks for invalid user-defined Direction command
{
  switch (enteredMove)
  {
  case 'W':
    return(enteredMove);
    break;
  case 'S':
    return(enteredMove);
    break;
  case 'A':
    return(enteredMove);
    break;
  case 'D':
    return(enteredMove);
    break;
  default:
    Serial.println("Invalid entry, please retry.");
    return('X');
    break;
  }
}

int moveDuration()
{
  durationUser =0;
  while(durationUser ==0)
  {
    if (Serial.available() > 0)
    {
      durationUser = Serial.parseInt(); 
      Serial.println(durationUser);
      durationUser = checkDuration(durationUser);
    }
  }
}

int checkDuration(int enteredDuration)
//Checks user for invalid user defined Duration value
{
  if (enteredDuration <= 0 )
  {
    Serial.print(" is an Invalid Value, please try again.");
    Serial.println();
    return(0);
  }
  Serial.println();
  return (enteredDuration);
}

char moveRobo(int userInput)
{
  switch (userInput) 
  {
  case 'W':    // forward
  /*
    interruptSetUp();
    */
    digitalWrite (rightForward, HIGH);
    digitalWrite (rightReverse, LOW);
    digitalWrite (leftForward, HIGH);
    digitalWrite (leftReverse, LOW);
    pedal2Metal();
    break;
  case 'S':    // reverse
    digitalWrite (rightForward, LOW);
    digitalWrite (rightReverse, HIGH);
    digitalWrite (leftForward, LOW);
    digitalWrite (leftReverse, HIGH);
    pedal2Metal();
    break;
  case 'D':    // left
    for(int time = 0; time <= durationUser; time++)
    {
      digitalWrite (rightForward, HIGH);
      digitalWrite (rightReverse, LOW);
      digitalWrite (leftForward, HIGH);
      digitalWrite (leftReverse, LOW);
      turnLeft();
      tone(audioPin, volume);
      Serial.println(time);
      Serial.println(volume);
      delay(1000);
    }
    break;
  case 'A':    // right
    for(int time = 0; time <= durationUser; time++)
    {
      digitalWrite (rightForward, HIGH);
      digitalWrite (rightReverse, LOW);
      digitalWrite (leftForward, HIGH);
      digitalWrite (leftReverse, LOW);
      turnRight();
      tone(audioPin, volume);
      Serial.println(time);
      Serial.println(volume);
      delay(1000);
    }
    break;
  } 
}

int pedal2Metal()
{
  interruptSetUp();
  if(speed > 200) // normally 128
  {
    for(int time = 0; time <= durationUser*1000; time++)
    {
      if (speed >=200)
      {
        if (rwheelPulse<=lwheelPulse) analogWrite(rightOut, speed);
        else analogWrite(rightOut, 255);
        // Send values to H-bridges
        if (lwheelPulse<=rwheelPulse) analogWrite(leftOut, speed);
        else analogWrite(leftOut, 255);
        /*
        tone(audioPin, volume);
        Serial.println(volume);
        volume++;
        */
        speed--;
      }
      delay(1);
    }
  }
}

int turnLeft()
{
  if(speed > 128)
  {
    for (speedUp = speed; speed >=128; speed--)
    {
      analogWrite(rightOut, speed);
      // Send values to H-bridges
      analogWrite(leftOut, speed/2);
      tone(audioPin, volume,10);
      Serial.println(volume);
      volume++;
    }
    delay(durationUser);
  }
}

int turnRight()
{
  if(speed > 128)
  {
    for (speedUp = speed; speed >=128; speed--)
    {
      analogWrite(rightOut, speed/2);
      // Send values to H-bridges
      analogWrite(leftOut, speed);
      tone(audioPin, volume,10);
      Serial.println(volume);
      volume++;
    }
    delay(durationUser);
  }
}

int slowMo()
{
  for (slowDown = speed; speed <=255; speed++)
    // loop for decel. – NOTE:  0 = fastest, 255 = off
  {
    analogWrite(rightOut, speed);
    analogWrite(leftOut, speed);
    tone(audioPin, volume,10);
    // do the decel in steps of 100 milliseconds to stop in 1.2 seconds
    Serial.println(volume);
    volume--;
  }
  Serial.println("Mission Complete...");
}


void lwheelSensor()      // Interrupt Loops
{
  readSensors();
  if(LWsensor <= 700)
  {
    lwheelPulse++;
    Serial.println(lwheelPulse);
  }
  if(lwheelPulse>rwheelPulse)
  {
    return;
  }
  if(lwheelPulse>=16)
  {
    lwheelPulse = 0;
    rwheelPulse = 0;
  }
}

void rwheelSensor()
{
  readSensors();
  if(RWsensor <= 700)
  {
    rwheelPulse++;
    Serial.println(rwheelPulse);
  }
  if(rwheelPulse>lwheelPulse)
  {
    return;
  }
  if(rwheelPulse>=16)
  {
    rwheelPulse = 0;
    lwheelPulse = 0;
  }
}

int readSensors()
{
  LWsensor = analogRead(A0);
  Serial.println(LWsensor);
  RWsensor = analogRead(A1);
  Serial.println(RWsensor);
}















