#include <Servo.h>

Servo servoTapa;

const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 8;

bool tapaAbierta = false;

void setup() {

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoTapa.attach(servoPin);
  servoTapa.write(0);

}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH);

  float distancia = duracion * 0.0343 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia <= 50 && !tapaAbierta) {

    servoTapa.write(90);

    tapaAbierta = true;

    Serial.print("USO,");
    Serial.println(distancia);

  }

  else if (distancia >= 55 && tapaAbierta) {

    servoTapa.write(0);

    tapaAbierta = false;

  }

  delay(100);

}