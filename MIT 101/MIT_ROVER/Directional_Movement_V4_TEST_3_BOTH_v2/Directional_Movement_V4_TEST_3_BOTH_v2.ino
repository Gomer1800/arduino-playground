//Wheel speed Calbiration and Sensor test
int leftOut= 5;    // Use output Pin 6 for PWM
int rightOut = 6;
const int leftForward = 11; //LF
const int leftReverse = 10; // LR
const int rightReverse= 9; // RR
const int rightForward = 4; // RF

volatile int lwheelPulse = 0;
volatile int rwheelPulse = 0;
volatile int Lflag = 0;
volatile int Rflag = 0;
int LWsensor;
int RWsensor;

char directionUser;
int durationUser;
int speed = 240;
int loopCount = 0;

void setup() 
{
  portConfiguration(); 
  hBridgeSetUp();
  interruptSetUp();
}

void hBridgeSetUp() // initialize digital I/O
{
  pinMode(leftForward, OUTPUT); 
  pinMode(leftReverse, OUTPUT);
  pinMode(rightForward, OUTPUT); 
  pinMode(rightReverse, OUTPUT);
}

void portConfiguration()    // setup functions
{
  Serial.begin(9600);
}

void interruptSetUp()
{
  attachInterrupt(0, lwheelSensor, RISING);
  attachInterrupt(1, rwheelSensor, RISING);
}

void loop() 
{
  reset();
  userInterface();
  moveRobo(directionUser);
}
int reset()
{
  noInterrupts();
  loopCount = 0;
  lwheelPulse = 0;
  rwheelPulse = 0;
  Lflag = 0;
  Rflag = 0;
  interrupts();
}

int userInterface()    // loop functions
{
  Serial.println("Awaiting your command pilot");
  Serial.println("You can select W(forward)or S(reverse)");
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
    digitalWrite (leftForward, HIGH);
    digitalWrite (leftReverse, LOW);
    digitalWrite (rightForward, HIGH);
    digitalWrite (rightReverse, LOW);
    pedal2Metal();
    break;
  case 'S':    // reverse
    digitalWrite (leftForward, LOW);
    digitalWrite (leftReverse, HIGH);
    digitalWrite (rightForward, LOW);
    digitalWrite (rightReverse, HIGH);
    pedal2Metal();
    break;
  } 
}

int pedal2Metal()
{
  while(rwheelPulse < 16||lwheelPulse < 16)
  {
    //for(int time = 0; time < 20; time++)
    //{
    if (speed >200)
    {
      speed--;
    }
    if (rwheelPulse<=lwheelPulse) analogWrite(rightOut, speed);
    //else analogWrite(rightOut, speed);
    // Send values to H-bridges
    if (lwheelPulse<=rwheelPulse) analogWrite(leftOut, speed);
    //else analogWrite(leftOut, speed);
    if(Rflag == 1||Lflag == 1)
    {
      analogWrite(leftOut, 255);
      analogWrite(rightOut, 255);
      Serial.println();
      Serial.print("Speed: ");
      Serial.print(speed);
      Serial.print("          ");
      Serial.print("lwheelPulse: ");
      Serial.print(lwheelPulse);
      Serial.print(" ");
      Serial.print("rwheelPulse: ");
      Serial.print(rwheelPulse);
      Serial.print("          ");
      LWsensor = analogRead(A0);
      RWsensor = analogRead(A1);
      Serial.print("LWSensor :");
      Serial.print(LWsensor);
      Serial.print(" ");
      Serial.print("RWSensor :");
      Serial.print(RWsensor);
      Serial.print("          ");
      Serial.print("Lflag :");
      Serial.print(Lflag);
      Serial.print(" ");
      Serial.print("Rflag :");
      Serial.print(Rflag);
      Serial.println();
      Lflag = 0;
      Rflag = 0;
    }
    loopCount++;
    // }
  }
  Serial.println();
  Serial.print("Loop Count: ");
  Serial.print(loopCount);
  Serial.print("          ");
  Serial.print("Final Pulse Count: ");
  Serial.print(lwheelPulse);
  Serial.print(" & ");
  Serial.print(rwheelPulse);
  Serial.println();
  speed = 255;
  analogWrite(leftOut, speed);
  analogWrite(rightOut, speed);
}

void lwheelSensor()      // Interrupt Loops
{
  lwheelPulse++;
  Lflag = 1;

}

void rwheelSensor()      // Interrupt Loops
{
  rwheelPulse++;
  Rflag = 1;

}

































