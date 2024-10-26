#include "arduino_secrets.h"

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#define Relay 4

const char DEVICE_LOGIN_NAME[] = "c78db72e-235e-4a83-881b-5ed33c01dcf7";
const char SSID[] = "*****";
const char PASS[] = "Ajinky@19";   
const char DEVICE_KEY[] = "h5xy8EQEic@khwELFyLaoSG?V"; 

CloudSwitch hOME;

void onHOMEChange();

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(hOME, READWRITE, ON_CHANGE, onHOMEChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {

  Serial.begin(9600);
  delay(1500);
  pinMode(Relay, OUTPUT);


  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

// Called every time a new value is received from IoT Cloud for hOME
void onHOMEChange() {
  if (hOME) {
    digitalWrite(Relay, HIGH);
    Serial.println("Relay ON");
  } else {
    digitalWrite(Relay, LOW);
    Serial.println("Relay OFF");
  }
}
