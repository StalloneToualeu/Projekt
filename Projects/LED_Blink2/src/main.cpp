#include <Arduino.h>

#define ledrot  D0



void setup() {
  Serial.begin(9600);
  Serial.println("connected");

  pinMode(ledrot, OUTPUT);
}

void loop() {
  digitalWrite(ledrot, HIGH);
  delay(1000);
  digitalWrite(ledrot, LOW);
  delay(1000);
}