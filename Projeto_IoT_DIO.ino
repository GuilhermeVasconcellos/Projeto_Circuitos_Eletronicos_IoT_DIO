
/*
Projeto de Circuitos Eletrônicos - IoT - DIO
Guilherme T. Vasconcellos

Descrição:
Neste projeto, simulando uma estufa de hortaliças, deve ser desenvolvido um circuito eletrônico,
envolvendo um sensor de temperatura, uma buzina, um LED e um motor, controlados por meio de um Arduino.
O projeto deve seguir a seguinte funcionalidade:
(a) Fazer a leitura da temperatura;
(b) Fazer o acionamento de um motor de ventilador caso a temperatura seja igual ou maior a 30 °C;
(c) Caso a temperatura ultrapasse os 50 °C, um LED vermelho e uma buzina devem acionar avisando uma situação de emergência.
Todo o processo descrito deve ser programado em linguagem C na placa de projetos Arduino.
*/
#include <TMP36.h>

#define SENSOR              A0
#define MOTOR               7
#define LED                 8
#define BUZZER              9
#define INTERVALO_LEITURAS  1000
int temp = 0;

void setup() {
  pinMode(SENSOR, INPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT); 
  Serial.begin(9600);
  Serial.println("Inicializando...");
  Serial.println("Pronto para receber leituras de temperatura...");
  setaEstadoNormal();
}

void setaEstadoNormal() {
  digitalWrite(MOTOR, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);
}

int converteTempToCelsius(int temp) {
	return (temp - 104) / 2;
}

void loop() {
  temp = converteTempToCelsius(analogRead(SENSOR));
  Serial.print("### Temperatura atual: ");
  Serial.print(temp);
  Serial.println(" C ###");

  if(temp >= 30) {
    Serial.println("Temperatura acima do normal... acionando o ventilador...");
    digitalWrite(MOTOR, HIGH);    
  }
  if(temp > 50) {
    Serial.println("PERIGO... temperatura muito alta... acionando o alarme...");
    digitalWrite(LED, !digitalRead(LED));
    digitalWrite(BUZZER, !digitalRead(BUZZER));
  }
  if(temp < 30) {
    setaEstadoNormal();
  }
  delay(INTERVALO_LEITURAS);
}