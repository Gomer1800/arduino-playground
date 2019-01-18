/* Test program for hardware interrupts. Outputs funny lines when interrupt triggered
 * 
 * created by Luis Gomez 2015
 */

int yellowLED = 13;
volatile boolean flashFast = false;		// Use on-board LED
int count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(yellowLED, OUTPUT);    		// define output pin
  digitalWrite(2, HIGH);
  attachInterrupt(0, interruptPoint , FALLING);	
}

void loop()
{
  int delayTime = 1000;  // define a local variable
  if (flashFast) delayTime = 100;  // same as if (flashFast == 1)
  digitalWrite (yellowLED, HIGH);
  delay(delayTime);
  Serial.println(delayTime);
  digitalWrite (yellowLED, LOW);
  delay(delayTime);
  Serial.println(delayTime);
}

void interruptPoint()				// ISR
{
  flashFast = ! flashFast;    // toggle value to on / off
  switch(count)
  {
  case 0:
    Serial.println("Hello World!");
    count++;
    break;
  case 1:
    Serial.println("Ouch! What did you do that for?");
    count++;
    break;
  case 2:
    Serial.println("Pick on somebody your own size!");
    count++;
    break;
  case 3:
    Serial.println("How would you feel if I got up and poked your head for a change?");
    count++;
    break;
  case 4:
    Serial.println("Oh, woe is me... I give up");
    count++;
    break;
  default:
    count = 0;
    break;
  }
}
