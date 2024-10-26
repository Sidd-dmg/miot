#include "arduino_secrets.h"

#define SENSOR_PIN 2    
#define RELAY_PIN 4     

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  int value = analogRead(SENSOR_PIN);

  Serial.print("Analog output: ");
  Serial.println(value);

  delay(1000);

  if (value < 500) { 
    Serial.println("The soil moisture is DRY => activate pump");
    digitalWrite(RELAY_PIN, HIGH);
    delay(500);
  } else {
    Serial.println("The soil moisture is WET => deactivate the pump");
    digitalWrite(RELAY_PIN, LOW);
    delay(500);
  }

  delay(100);
}
