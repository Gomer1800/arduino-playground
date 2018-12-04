int EN = 125;
int QN = 250;
int HN = 500;
int TQN = 750;
int A = 440;
int D = 294;
int F = 349;
int G = 392;
int C = 262;
int E = 330;
int HB = 494;
int HC = 523;
int HD = 587;


void setup()
{
  Title();
}

void loop()
{
  playMusic();
  Serial.println("Bravo!");
  Serial.println();
}

void Title()
{
   Serial.println("Drunken Sailor V1.0");
   Serial.println();
}

int playMusic()
{
  tone(7,A,QN);
  delay(50);
  tone(7,A,EN);
  delay(50);
  tone(7,A,EN);
  delay(50);
  tone(7,A,QN);
  delay(50);
  tone(7,A,EN);
  delay(50);
  tone(7,A,EN);
  delay(50);
  tone(7,A,QN);
  delay(50);
  tone(7,D,QN);
  delay(50);
  tone(7,F,QN);
  delay(50);
  tone(7,A,QN);
  delay(50);
  tone(7,G,QN);
  delay(50);
  tone(7,G,EN);
  delay(50);
  tone(7,G,EN);
  delay(50);
  tone(7,G,QN);
  delay(50);
  tone(7,G,EN);
  delay(50);
  tone(7,G,EN);
  delay(50);
  tone(7,G,QN);
  delay(50);
  tone(7,C,QN);
  delay(50);
  /*
  tone(7,E,QN);
  delay(50);
  tone(7,G,QN);
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();  
  delay(50
  tone();
  delay(50);
  tone();
  delay(50
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  tone();
  delay(50);
  */
  
}
