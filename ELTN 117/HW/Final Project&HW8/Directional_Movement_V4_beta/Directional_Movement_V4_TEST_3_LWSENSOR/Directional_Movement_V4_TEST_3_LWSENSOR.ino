//Wheel speed Calbiration and Sensor test
int leftOut= 5;    // Use output Pin 6 for PWM
const int leftForward = 11; //LF
const int leftReverse = 10; // LR

volatile int lwheelPulse = 0;
volatile int Lflag = 0;
int LWsensor;

char directionUser;
int durationUser;
int speed = 255;
int time = 0;

void setup() 
{
  portConfiguration(); 
  hBridgeSetUp();
}

void hBridgeSetUp() // initialize digital I/O
{
  pinMode(leftForward, OUTPUT); 
  pinMode(leftReverse, OUTPUT);
}

void portConfiguration()    // setup functions
{
  Serial.begin(9600);
}

void interruptSetUp()
{
  attachInterrupt(0, lwheelSensor, RISING);
}

void loop() 
{
  reset();
  userInterface();
  interruptSetUp();
  moveRobo(directionUser);
}
int reset()
{
  time = 0;
  lwheelPulse = 0;
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
    pedal2Metal();
    break;
  case 'S':    // reverse
    digitalWrite (leftForward, LOW);
    digitalWrite (leftReverse, HIGH);
    pedal2Metal();
    break;
  } 
}

int pedal2Metal()
{
  while(lwheelPulse < 16)
  {
    //for(int time = 0; time < 20; time++)
    //{
    if (speed >245)
    {
      speed--;
    }
    analogWrite(leftOut, speed);
    if(Lflag == 1)
    {
      analogWrite(leftOut, 255);
      Serial.println();
      Serial.print("Speed: ");
      Serial.print(speed);
      Serial.print("          ");
      Serial.print("lwheelPulse: ");
      Serial.print(lwheelPulse);
      Serial.print("          ");
      LWsensor = analogRead(A0);
      Serial.print("LWSensor :");
      Serial.print(LWsensor);
      Serial.println();
      delay(1000);
      Lflag = 0;
    }
    time++;
    //delay(1);
    // }
  }
  Serial.println();
  Serial.print("Milliseconds: ");
  Serial.print(time);
  Serial.print("          ");
  Serial.print("Final Pulse Count: ");
  Serial.print(lwheelPulse);
  Serial.println();
  speed = 255;
  analogWrite(leftOut, speed);
}

void lwheelSensor()      // Interrupt Loops
{
  lwheelPulse++;
  //delay(1);
  Lflag = 1;
}





























