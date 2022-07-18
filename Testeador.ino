#include <Controllino.h>
//Puse varios print y println para que puedan hacer pruebas y entender mejor el funcionamiento
//Al momento de ya quedar en producción, eliminar todos los "Serial.println()" y "Serial.print()" 


//variables flobales

  /* El primer numero de la siguiente operación significa lo amperes a los que se debe de detener el alimentador.
   *  Ejemplo, si se busca que el alimentador se pare al 87% de capacidad debe de estár 8.7/0.03 */
float detenerAlimentador = 8.7/0.03;
int muestras = 8; //cantidad de muestas a promediar
int espera = 250; // tiempo entre muestra y muestra
int preatasco = 4000; //milesimas de segundos que se debe de esperar antes de volver a intentar avanzar 
int maximoPromedio = 0;
int maximoMuestra = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(CONTROLLINO_A3, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float cargaPromedio = calculoMotor();
  Serial.println(cargaPromedio*0.3);
  Serial.print("El maximo pico es de ");
  Serial.print(maximoMuestra);
  Serial.print(" recomendando configurar el limite de la quebradora a: ");
  Serial.println(maximoPromedio);
  delay(preatasco);

}

//funcion separada para medir el esfuerzo del motor
float calculoMotor()
{
  float motorCarga = 0;
  float acomulador = 0;
  for(int i=0;i<muestras;i++)
  {
    motorCarga = analogRead(CONTROLLINO_A3);
    if (motorCarga > maximoMuestra){
      maximoMuestra = motorCarga;
      Serial.print("Nueva muestra unica Máxima --->>> ");
      Serial.println(maximoMuestra*0.3);
    }
    acomulador = acomulador + motorCarga;
    delay(espera);
    Serial.print("muestra individual: ");
    Serial.println(motorCarga*0.3);
  }
  acomulador = acomulador/muestras;
  if (acomulador > maximoPromedio){
    maximoPromedio = maximoPromedio;
    Serial.print("Nueva muestra Máximo Promedio  =====>>>>>>> ");
    Serial.println(maximoPromedio*0.3);
  }
  Serial.print("acomulado promedio ---->>> ");
  return(acomulador);
}

/* Si el controllino se maneja en 24V cada punto en el input es igual a "1 digit = 0,03V (30,0mV)"
*/
