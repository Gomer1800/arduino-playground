//Wheel speed Calbiration and Sensor test

volatile int lwheelPulse = 0;
//volatile int rwheelPulse = 0;
volatile int Lflag = 0;
int LWsensor;
//int RWsensor;

void setup() 
{
  portConfiguration(); 
  interruptSetUp();
}

void portConfiguration()    // setup functions
{
  Serial.begin(9600);
}

void interruptSetUp()
{
  attachInterrupt(0, lwheelSensor, FALLING);
  //attachInterrupt(1, rwheelSensor, FALLING);
}

void loop() 
{
  if(Lflag == 1)
  {
  Serial.println();
  Serial.print("lwheelPulse: ");
  Serial.print(lwheelPulse);
  Serial.print("          ");
  LWsensor = analogRead(A0);
  Serial.print("LWSensor :");
  Serial.print(LWsensor);
  Serial.println();
  Lflag = 0;
  interrupts();
  }
  /*
  Serial.print("rwheelPulse: ");
  Serial.println(rwheelPulse);
  RWsensor = analogRead(A1);
  Serial.println("RWSensor :");
  Serial.print(RWsensor);
  delay(250);
  */
  /*
  if(lwheelPulse>rwheelPulse)
   {
   return;
   }
   if(lwheelPulse>=16)
   {
   lwheelPulse = 0;
   rwheelPulse = 0;
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
   */
}

void lwheelSensor()      // Interrupt Loops
{
  lwheelPulse++;
  delay(250);
  Lflag = 1;
  noInterrupts();
}

/*
void rwheelSensor()
{
  rwheelPulse++;
}

int readSensors()
{
  LWsensor = analogRead(A0);
  RWsensor = analogRead(A1);
}
*/




















