#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define TRIG_PIN 33
#define ECHO_PIN 32

const char* ssid = "NomDuWifi";
const char* password = "MDPWIFI";
const char* serverUrl = "http://ip:port/alert";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connecté !");

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.0344 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 150) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"distance\":" + String(distance) + "}";
    int httpResponseCode = http.POST(json);

    Serial.print("Réponse HTTP: ");
    Serial.println(httpResponseCode);

    http.end();
  }

  delay(10000);
}
