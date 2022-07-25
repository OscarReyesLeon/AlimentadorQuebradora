#include <Controllino.h>

float detenerAlimentador = 8.0/0.03;
float prenderAlimentador = 0.5/0.03;
int muestras = 16;
int espera = 63;

void setup() {
  pinMode(CONTROLLINO_A3, INPUT);
  pinMode(CONTROLLINO_D2, OUTPUT);
  pinMode(CONTROLLINO_D6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float cargaPromedio = calculoMotor();
  if (cargaPromedio > detenerAlimentador){
    digitalWrite(CONTROLLINO_D2, 0);
    for(int i=0;i<12;i++)
    {
      digitalWrite(CONTROLLINO_D6, 1);
      delay(50);
      digitalWrite(CONTROLLINO_D6, 0);
      delay(50);
      digitalWrite(CONTROLLINO_D6, 1);
      delay(50);
      digitalWrite(CONTROLLINO_D6, 0);
      delay(100);
    }
  } else if(cargaPromedio <= detenerAlimentador & cargaPromedio >= prenderAlimentador){
    digitalWrite(CONTROLLINO_D2, 1);
    digitalWrite(CONTROLLINO_D6, 1);
  } else if(cargaPromedio < prenderAlimentador){
    digitalWrite(CONTROLLINO_D2, 0);
    for(int i=0;i<60;i++)
    {
      digitalWrite(CONTROLLINO_D6, 1);
      delay(5000);
      digitalWrite(CONTROLLINO_D6, 0);
      delay(5000);
    } 
  } else {
    digitalWrite(CONTROLLINO_D2, 0);
    digitalWrite(CONTROLLINO_D6, 0);
  }

  
}

float calculoMotor()
{
  float motorCarga = 0;
  float acomulador = 0;
  for(int i=0;i<muestras;i++)
  {
    motorCarga = analogRead(CONTROLLINO_A3);
    acomulador = acomulador + motorCarga;
    delay(espera);
  }
  acomulador = acomulador/muestras;
  return(acomulador);
}
