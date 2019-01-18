/*
 * 2/1/15
 * Created by: Luis Gomez
 */
 
void setup()
{
  portConfiguration();
}

void loop()
{
}

// Functions defined below

void portConfiguration()
// Intitiates serial port for 9600 baud and displays program title
{
   Serial.begin(9600);
   Serial.println("Pulse Generator V1.0");
}
