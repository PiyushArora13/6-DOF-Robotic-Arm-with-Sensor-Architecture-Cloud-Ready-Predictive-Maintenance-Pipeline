

#include <WiFi.h>


const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";


String incomingData = "";
unsigned long lastCloudPush = 0;


void setup() {
  Serial.begin(115200);      // Debug
  Serial2.begin(115200);     // ESP32 ← Arduino Mega

  connectWiFi();
}

void loop() {

  receiveFromArduino();

  if (WiFi.status() == WL_CONNECTED) {
    if (millis() - lastCloudPush > 2000) {
      pushToCloud(incomingData);
      lastCloudPush = millis();
    }
  } else {
    handleOfflineMode();
  }
}



void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
}

void receiveFromArduino() {
  while (Serial2.available()) {
    char c = Serial2.read();
    incomingData += c;

    if (c == '\n') {
      Serial.println("Received: " + incomingData);
    }
  }
}

void pushToCloud(String data) {
  
  Serial.println("Pushing data to cloud...");
}

void handleOfflineMode() {

  Serial.println("Offline mode: buffering data");
}
