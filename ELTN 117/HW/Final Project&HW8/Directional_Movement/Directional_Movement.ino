// Setup Variables
int rightOut = 5;  // Use output Pin 5 for PWM
int leftOut= 6;    // Use output Pin 6 for PWM
const int leftForward = 11;
const int leftReverse = 10;

const int rightForward = 2;
const int rightReverse = 3;

// Direction commands
char input;
/*
const int forward = 'W';
const int reverse = 'S';
const int left = 'A';
const int right = 'D';
*/

int speed;
int slowDown;
int delayTime;
int leftSpeed = 128;		// Move at medium speed
int rightSpeed = 141;	// same for right motor
int time1 = 10;		// Run forward for ten seconds

void setup() 
{
  portConfiguration(); 
  hBridgeSetUp();
}

void loop() 
{
  userInterface();
  changeDirection(input);    // Calls the function that changes direction
  delay(2000);
  pedal2Metal();
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
  Serial.println("Awaiting your command pilot");
  Serial.println("You can select W(forward), A(left), D(right), or S(reverse)");
  Serial.println();
  
  int count =0;
  while(count ==0)
  {
   if (Serial.available() > 0)
      {
        input = Serial.read(); 
        Serial.println();
        return input;
      }
  }
}

int changeDirection(int robotDirection)
{
    switch (robotDirection) 
    {
  case 'W':    // forward
    digitalWrite (rightForward, HIGH);
    digitalWrite (rightReverse, LOW);
    digitalWrite (leftForward, HIGH);
    digitalWrite (leftReverse, LOW);
    break;
  case 'S':    // reverse
    digitalWrite (rightForward, LOW);
    digitalWrite (rightReverse, HIGH);
    digitalWrite (leftForward, LOW);
    digitalWrite (leftReverse, HIGH);
    break;
  case 'A':    // left
    digitalWrite (rightForward, HIGH);
    digitalWrite (rightReverse, LOW);
    digitalWrite (leftForward, LOW);
    digitalWrite (leftReverse, HIGH);
    break;
  case 'D':    // right
    digitalWrite (rightForward, LOW);
    digitalWrite (rightReverse, HIGH);
    digitalWrite (leftForward, HIGH);
    digitalWrite (leftReverse, LOW);
    break;
  break;
  } 
}

int pedal2Metal()
{
  Serial.print(input);
  analogWrite(rightOut, rightSpeed);	// Send values to H-bridges
  analogWrite(leftOut, leftSpeed);
  for (delayTime = 0; delayTime < time1; delayTime++)	//  Go forward for ten seconds
  {
     delay(1000);	// delay one second;		// “Nested” delay allows more incremental control
  }
  speed = 128;	
  for (slowDown = speed; speed <255; speed++)	// loop for decel. – NOTE:  0 = fastest, 255 = off
  {
    delay(10);	// do the decel in steps of 100 milliseconds to stop in 1.2 seconds
    analogWrite(rightOut, speed);
    analogWrite(leftOut, speed);
  
  }
}
