//Wheel speed Calbiration and Sensor test


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
  attachInterrupt(0, lwheelSensor, RISING);
  attachInterrupt(1, rwheelSensor, RISING);
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
  if(speed > 225) // normally 128
  {
    for(int time = 10; time <= time*100; time++)
    {
      if (speed >=225)
      {
        /*
        readSensors();
         */
        Serial.print("LEFT: ");
        Serial.println(LWsensor);
        Serial.print("RIGHT: ");
        Serial.println(RWsensor);
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
      delay(10);
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
  /*
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
   */
  Serial.println("Mission Complete...");
}


void lwheelSensor()      // Interrupt Loops
{
  readSensors();
  if(LWsensor <= 500)
    /*
  {
     */
    lwheelPulse++;
  Serial.print("lwheelPulse: ");
  Serial.println(lwheelPulse);
  /*
  }
   */
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
  /*
  readSensors();
   */
  Serial.print("Interrupt Triggered,LEFT: ");
  Serial.println(LWsensor);
  RWsensor = analogRead(A1);
  Serial.print("Interrupt Triggered,RIGHT: ");
  Serial.println(RWsensor);
  /*
  if(RWsensor <= 500)
   {
   */
  rwheelPulse++;
  Serial.println("rwheelPulse: ");
  Serial.println(rwheelPulse);
  /*
  }
   */
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
  RWsensor = analogRead(A1);
}

















