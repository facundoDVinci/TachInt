/*
---------------------------------------------------------
PROYECTO: Tacho de Basura Inteligente
Nombre: Tachint
Autor: Facundo Leonel
Descripción: Este programa controla un tacho de basura automático 
utilizando un sensor ultrasónico y un microservomotor. 
Cuando una persona acerca la mano, la tapa se abre automáticamente y se registra el uso 
mediante el puerto serie.
---------------------------------------------------------
*/

#include <Servo.h>   // Librería para controlar el servomotor

Servo servoTapa;      // Objeto que controla el servomotor

// Pines utilizados por el sensor ultrasónico y el servo
const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 8;

bool tapaAbierta = false; // Esta variable indica si la tapa está abierta o cerrada.
// Se utiliza para evitar registrar múltiples usos mientras la mano permanece frente al sensor.


// La función setup() se ejecuta una sola vez al iniciar el Arduino.
// Configura la comunicación serie, los pines y la posición inicial del servomotor.
void setup() {

  Serial.begin(9600); // Inicializa la comunicación serie a 9600 baudios

  // Configuración de los pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoTapa.attach(servoPin); // Configuración del servomotor

  servoTapa.write(0); // Posición inicial: tapa cerrada

}


// La función loop(): Se ejecuta continuamente mientras el Arduino permanezca encendido.
// Los pasos son:
// 1. Mide la distancia mediante el sensor ultrasónico.
// 2. Si la mano está cerca (menos o igual a 50 cm), abre la tapa.
// 3. Envía un mensaje por el puerto serie indicando el uso.
// 4. Cuando la mano se aleja (mayor o igual a 55 cm), vuelve a cerrar la tapa.
void loop() {

  // Genera el pulso de disparo del sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH); // Obtiene el tiempo que tarda el eco en regresar

  float distancia = duracion * 0.0343 / 2; // Convierte el tiempo recibido en distancia (cm)

  
  // Condición para abrir la tapa
  if (distancia <= 50 && !tapaAbierta) {

    
    servoTapa.write(90); // Abre la tapa

    tapaAbierta = true; // Indica que la tapa ya está abierta

    
    Serial.print("USO,");
    Serial.println(distancia); // Envía el evento al programa de Python

  }

 
  // Condición para cerrar la tapa
  else if (distancia >= 55 && tapaAbierta) {

  
    servoTapa.write(0);   // Cierra la tapa

  
    tapaAbierta = false;   // Indica que la tapa volvió a cerrarse

  }
  delay(100); // Pequeña pausa para estabilizar la lectura

}