#include "arduino_secrets.h"

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#define IN1 15
#define IN2 2
#define ENA 4

const char DEVICE_LOGIN_NAME[] = "f35b8ae2-8a48-435b-bbcf-d655b23f82a2";
const char SSID[] = "*****";
const char PASS[] = "Ajinky@19";   
const char DEVICE_KEY[] = "?KlOz58o6ttOSfIytPe0toYx6"; 

int dC_MOTOR; 

void onDCMOTORChange();

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(dC_MOTOR, READWRITE, ON_CHANGE, onDCMOTORChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(9600);
  delay(1500);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

void onDCMOTORChange()  {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, dC_MOTOR);
  Serial.print("MOTOR_SPEED : ");
  Serial.println(dC_MOTOR);
  
}
