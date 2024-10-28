#include <ESP32Servo.h> 

#define TRIG_PIN 12       // Trigger pin for ultrasonic sensor
#define ECHO_PIN 13       // Echo pin for ultrasonic sensor
#define SERVO_PIN 4       // Servo motor connected to GPIO 4

Servo myservo;
int currentAnglec = 10;

void setup() {
  Serial.begin(115200);
  myservo.attach(SERVO_PIN);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.write(currentAnglec);  // Initialize to start angle
}

void loop() {
  float distance = getDistance();  // Get distance from ultrasonic sensor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 10) { // If distance is less than 10 cm
    Open();
  }

  delay(100);  // Add a small delay to avoid rapid triggering
}

// Function to control the servo movement
void Open() {
  if (currentAnglec < 180) {  
    currentAnglec += 20;
    myservo.write(currentAnglec);
    delay(500);  // Give the servo time to move
  } 
  
  if (currentAnglec >= 180) {
    delay(7000);  // Pause at 180 before resetting
    currentAnglec = 0;  // Reset to 0 for next open cycle
    myservo.write(currentAnglec);
    delay(500);  // Give the servo time to move back
  }
}

// Function to measure distance using the ultrasonic sensor
float getDistance() {
  // Send a 10us pulse to trigger the sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin for the duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm (sound speed is 0.034 cm per microsecond)
  float distance = duration * 0.034 / 2;
  return distance;
}
