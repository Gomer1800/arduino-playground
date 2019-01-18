// Setup Variables
int rightOut = 5;  // Use output Pin 5 for PWM
int leftOut= 6;    // Use output Pin 6 for PWM
const int leftForward = 11;
const int leftReverse = 10;

const int rightForward = 2;
const int rightReverse = 3;

int volume;
int audioPin =7;

// User defined values in moveRobo function
char directionUser;
int durationUser;

int speed;
int speedUp;
int slowDown;
int delayTime;
/*
int leftSpeed = 128;	// Move at medium speed
int rightSpeed = 128;	// same for right motor	
*/

void setup() 
{
  portConfiguration(); 
  hBridgeSetUp();
}

void loop() 
{
  userInterface();
  moveRobo(directionUser);    // Moves robot according to user defined directional & duration values
  slowMo(); // Slows down robot
}

// setup functions

void portConfiguration()
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

// loop functions

int userInterface()
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
  directionUser =0;
  while(directionUser ==0)
  {
    if (Serial.available() > 0)
    {
      directionUser = Serial.read(); 
      Serial.println(directionUser);
      directionUser = checkMove(directionUser);
    }
  }
}

// Checks for invalid user-defined Direction command
char checkMove(char enteredMove)
{
  switch (enteredMove)
  {
    case 'W':
    break;
    case 'S':
    break;
    case 'A':
    break;
    case 'D':
    break;
    default:
    enteredMove = 0;
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
      durationUser = Serial.read(); 
      Serial.println(durationUser);
      durationUser = checkDuration(durationUser);
    }
  }
}

//Checks user for invalid user defined Duration value
int checkDuration(int enteredDuration)
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

int moveRobo(int userInput)
{
  switch (userInput) 
  {
  case 'W':    // forward
    for(int time = 0; time <= durationUser; time++)
    {
      digitalWrite (rightForward, HIGH);
      digitalWrite (rightReverse, LOW);
      digitalWrite (leftForward, HIGH);
      digitalWrite (leftReverse, LOW);
      pedal2Metal(); // Runs motors
      delay(1000);
    }
    break;
  case 'S':    // reverse
    for(int time = 0; time <= durationUser; time++)
    {
      digitalWrite (rightForward, LOW);
      digitalWrite (rightReverse, HIGH);
      digitalWrite (leftForward, LOW);
      digitalWrite (leftReverse, HIGH);
      pedal2Metal();
      delay(1000);
    }
    break;
  case 'A':    // left
    for(int time = 0; time <= durationUser; time++)
    {
      digitalWrite (rightForward, HIGH);
      digitalWrite (rightReverse, LOW);
      digitalWrite (leftForward, LOW);
      digitalWrite (leftReverse, HIGH);
      pedal2Metal();
      delay(1000);
    }
    break;
  case 'D':    // right
    for(int time = 0; time <= durationUser; time++)
    {
      digitalWrite (rightForward, LOW);
      digitalWrite (rightReverse, HIGH);
      digitalWrite (leftForward, HIGH);
      digitalWrite (leftReverse, LOW);
      pedal2Metal();
      delay(1000);
    }
    break;
  } 
}

int pedal2Metal()
{
  speed =255;
  volume = 0;
  for (speedUp = speed; speed >128; speed--)
  {
    analogWrite(rightOut, speed);	// Send values to H-bridges
    analogWrite(leftOut, speed);
    tone(audioPin, volume,10);
    volume++;
  }
}

int slowMo()
{
  for (slowDown = speed; speed <255; speed++)	// loop for decel. – NOTE:  0 = fastest, 255 = off
  {
    analogWrite(rightOut, speed);
    analogWrite(leftOut, speed);
    tone(audioPin, volume,10);	// do the decel in steps of 100 milliseconds to stop in 1.2 seconds
    volume--;
  }
  Serial.println("Mission Complete...");
}

