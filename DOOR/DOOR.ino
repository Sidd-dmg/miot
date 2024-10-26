#include "arduino_secrets.h"

#include <ESP32Servo.h> 

#define IR 2
Servo myservo;
int currentAnglec = 10;

void setup() {
  Serial.begin(9600);
  myservo.attach(4);
  pinMode(IR, INPUT);
  myservo.write(currentAnglec);  // Initialize to start angle
}

void loop() {
  int IRval = digitalRead(IR);
  Serial.print("IR Value: ");
  Serial.println(IRval);

  if (IRval == LOW) {
    Open();
  }
}

void Open() {
  if (currentAnglec < 180) {  
    currentAnglec += 20;
    myservo.write(currentAnglec);
    delay(500);  
  } 
  
  if (currentAnglec >= 180) {
    delay(8000);  
    currentAnglec = 0;  
    myservo.write(currentAnglec);
    delay(500);  
  }
}

