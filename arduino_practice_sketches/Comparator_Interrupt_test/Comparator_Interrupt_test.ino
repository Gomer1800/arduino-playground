int ledPin = 13;
int optic1;
int optic2;

void setup()
{ 
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(0, stuffHappened, RISING);
  attachInterrupt(1, stuffHappened, RISING);
}

void loop()
{
  optic1 = analogRead(A0);
  optic2 = analogRead(A1);
}

void stuffHappened()
{
  digitalWrite(ledPin, HIGH);
  Serial.println(optic1);
  Serial.println(optic2);
  delay(500);
  Serial.println("Interrupt Triggered");
  digitalWrite(ledPin, LOW);
}

