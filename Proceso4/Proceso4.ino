#include <Controllino.h>

float detenerAlimentador = 8.0/0.03;
int muestras = 16;
int espera = 250;
int tciclo = 2000;

void setup() {
  pinMode(CONTROLLINO_A3, INPUT);
  pinMode(CONTROLLINO_D2, OUTPUT);
  pinMode(CONTROLLINO_D3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float cargaPromedio = calculoMotor();

  if (cargaPromedio <= detenerAlimentador){
    digitalWrite(CONTROLLINO_D2, 1);
    digitalWrite(CONTROLLINO_D3, 1);
    delay(tciclo);
  }
  else{
    digitalWrite(CONTROLLINO_D2, 0);
    digitalWrite(CONTROLLINO_D3, 0);
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