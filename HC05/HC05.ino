const int ledPin = 13;   // Built-in LED pin

void setup() {
  Serial.begin(9600);    // Start serial communication for HC-05
  pinMode(ledPin, OUTPUT); // Set LED pin as output
}

void loop() {
  if (Serial.available() > 0) {     // Check if data is available
    char receivedChar = Serial.read(); // Read the incoming byte
    
    if (receivedChar == 'A') {       // If 'A' is received
      digitalWrite(ledPin, HIGH);    // Turn on the LED
      Serial.println("LED ON");      // Optional feedback
    } 
    else if (receivedChar == 'B') {  // If 'B' is received
      digitalWrite(ledPin, LOW);     // Turn off the LED
      Serial.println("LED OFF");     // Optional feedback
    }
  }
}