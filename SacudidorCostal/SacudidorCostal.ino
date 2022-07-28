//echo con arduino nano y un shield de optoacpladores y relevadores.
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2;i<=7;i++)
  {
    digitalWrite(i, 1);
    digitalWrite(13, 0);
    delay(2000);
    digitalWrite(i, 0);
    delay(15000);
    for(int led=1;led<=5;led++)
    {
      digitalWrite(13, 1);//3
      delay(500);
      digitalWrite(13, 0);
      delay(500);
    }

   }      
}
