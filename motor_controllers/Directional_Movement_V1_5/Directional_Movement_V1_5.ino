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
char directionCommand;
int moveDuration;

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
  moveRobo(directionCommand);    // Moves robot according to user defined directional & duration values
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

  for(int count1 =0;count1 <1; count1++);
  {
    if (Serial.available() > 0)
    {
      directionCommand = Serial.read(); 
      Serial.println(directionCommand);
    }
  }
  Serial.println("For how many seconds would you like the robot to move pilot?");
  for(int count1 =0;count1 <1; count1++);
  {
    if (Serial.available() > 0)
    {
      moveDuration = Serial.read(); 
      Serial.println(moveDuration);
    }
  }
}

int moveRobo(int userInput)
{
  switch (userInput) 
  {
  case 'W':    // forward
    for(int time = 0; time <= moveDuration; time++)
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
    for(int time = 0; time <= moveDuration; time++)
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
    for(int time = 0; time <= moveDuration; time++)
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
    for(int time = 0; time <= moveDuration; time++)
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

