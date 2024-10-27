#include <WiFi.h>

// WiFi credentials
const char* ssid = "wifi";
const char* password = "123456789";

// Relay pin
const int relayPin = 8;  // Change to the GPIO pin you’re using

// Web server running on port 80
WiFiServer server(80);

// Variable to hold the relay state
bool relayState = LOW;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, relayState);  // Start with relay off

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the web server
  server.begin();
}

void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client connected.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        currentLine += c;

        // Check if request ends with a newline
        if (c == '\n') {
          // Check if it's a GET request for relay control
          if (currentLine.indexOf("GET /relay/on") >= 0) {
            relayState = HIGH;
            digitalWrite(relayPin, relayState);
          }
          if (currentLine.indexOf("GET /relay/off") >= 0) {
            relayState = LOW;
            digitalWrite(relayPin, relayState);
          }

          // Send HTML response to client
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();

          client.print("<html><body><h1>ESP32 Relay Control</h1>");
          client.print("<p>Relay is currently: ");
          client.print(relayState ? "ON" : "OFF");
          client.print("</p><p><a href=\"/relay/on\"><button>Turn On</button></a>");
          client.print("<a href=\"/relay/off\"><button>Turn Off</button></a></p>");
          client.print("</body></html>");

          // Close the HTTP response
          client.println();
          break;
        }
        if (c == '\n') currentLine = "";
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
  }
}