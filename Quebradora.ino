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
int tciclo = 2000; //milesimas de segundos que espera para repetir ciclo

void setup() {
  // put your setup code here, to run once:
  pinMode(CONTROLLINO_A3, INPUT);
  pinMode(CONTROLLINO_D2, OUTPUT);
  pinMode(CONTROLLINO_D3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  float cargaPromedio = calculoMotor();
  Serial.print("diferencia es igual: ");
  Serial.print((cargaPromedio - detenerAlimentador)*0.3);
  Serial.println(" Negativo es OK. / Si es positivo, el alimentador se debe parar.");

  
  if (cargaPromedio <= detenerAlimentador){
    //Aquí es si la quebradora está ok
    digitalWrite(CONTROLLINO_D2, 1); // Puerto de alimentador 
    digitalWrite(CONTROLLINO_D3, 0); // Puerto de luz indicadora 
    Serial.println("Quebradora ok |                 (づ๑•ᴗ•๑)づ♡");
  }
  else{
    //Aquí es si la quebradora se empieza a atascar
    digitalWrite(CONTROLLINO_D2, 0);  //Se detiene alimentador
    digitalWrite(CONTROLLINO_D3, 1);  //Se prende la luz indicadora
    Serial.println("preatastco |    Deteniendo alimentador");
    Serial.println("preatastco |                    (¬_¬ )");
    delay(preatasco);
  }
  delay(tciclo);
}

//funcion separada para medir el esfuerzo del motor
float calculoMotor()
{
  float motorCarga = 0;
  float acomulador = 0;
  for(int i=0;i<muestras;i++)
  {
    motorCarga = analogRead(CONTROLLINO_A3);
    acomulador = acomulador + motorCarga;
    delay(espera);
    Serial.print("muestra individual: ");
    Serial.println(motorCarga*0.3);
  }
  acomulador = acomulador/muestras;
  Serial.print("acomulado promedio ====>>> ");
  Serial.println(acomulador*0.3);
  return(acomulador);
}

/* Si el controllino se maneja en 24V cada punto en el input es igual a "1 digit = 0,03V (30,0mV)"
*/
