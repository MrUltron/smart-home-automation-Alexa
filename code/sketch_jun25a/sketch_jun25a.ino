// Smart Home Automation with Alexa (NodeMCU + Amazon Echo)
// Controls: Light, Fan, Door (Open/Close)

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define RELAY_LIGHT D1   // Light relay
#define RELAY_FAN D2     // Fan relay
#define RELAY_DOOR D3    // Door relay (open/close mechanism)

fauxmoESP fauxmo;

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected.");
  Serial.println(WiFi.localIP());

  pinMode(RELAY_LIGHT, OUTPUT);
  pinMode(RELAY_FAN, OUTPUT);
  pinMode(RELAY_DOOR, OUTPUT);

  digitalWrite(RELAY_LIGHT, LOW);
  digitalWrite(RELAY_FAN, LOW);
  digitalWrite(RELAY_DOOR, LOW);

  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);

  fauxmo.addDevice("light");
  fauxmo.addDevice("fan");
  fauxmo.addDevice("door");

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("Device %s state: %s\n", device_name, state ? "ON" : "OFF");

    if (strcmp(device_name, "light") == 0) {
      digitalWrite(RELAY_LIGHT, state ? HIGH : LOW);
    } else if (strcmp(device_name, "fan") == 0) {
      digitalWrite(RELAY_FAN, state ? HIGH : LOW);
    } else if (strcmp(device_name, "door") == 0) {
      // Simulate door open/close with a pulse
      if (state) {
        digitalWrite(RELAY_DOOR, HIGH);
        delay(1000); // 1-second pulse to trigger door mechanism
        digitalWrite(RELAY_DOOR, LOW);
      }
    }
  });
}

void loop() {
  fauxmo.handle();
}
