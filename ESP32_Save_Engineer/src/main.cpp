#include <Arduino.h>

// put function declarations here:

int ledPin = 25;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  // put your main code here, to run repeatedly:
}
