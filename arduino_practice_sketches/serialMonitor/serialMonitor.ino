//Printing text to the Screen
int value;

void setup()
{
  Serial.begin(9600);
  Serial.println("Hello Dave, enter a number");
}
void loop()
{
  char ch; // defining a variable type "char" which means character.
    if (Serial.available()>0) //wait for the user to type something
    {
      value = Serial.parseInt(); //convert character to an integer called value
      Serial.println(value * 2);
      delay(1000);
    }
  
}

