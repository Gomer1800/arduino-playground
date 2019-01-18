int optic1;
int optic2;

void setup()
{
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop()
{
  optic1 = analogRead(A0);
  optic2 = analogRead(A1);
  delay(100);
  Serial.println(optic1);
  if (optic1>=500)
  {
    Serial.println("Black");
  }
  if (optic1<=400)
  {
    Serial.println("White");
  }
}


