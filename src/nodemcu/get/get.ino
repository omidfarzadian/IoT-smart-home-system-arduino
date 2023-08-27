#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>

// #define SSID "Lord of the Pings"
// #define PASS "7YWSKDAY"

#define SSID "Kav"
#define PASS "33457043"

#define BASE_URL "http://192.168.1.126:2501"

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
HTTPClient http;

int LED_STATUS = 0;
int HEATER_STATUS = 0;
int MOTOR_STATUS = 0;
int LIGHT_INTENSITY = 0;

void setup() {
  Serial.begin(115200);
  connectToWifi();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    LED_STATUS = getLightStatus();
    HEATER_STATUS = getHeaterStatus();
    MOTOR_STATUS = getMotorStatus();
    LIGHT_INTENSITY = getLightIntensity();

    Serial.print(LED_STATUS*4 + HEATER_STATUS*2 + MOTOR_STATUS);
    Serial.println(LIGHT_INTENSITY);
  }
  delay(1000);
}

void connectToWifi() {
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);
}

int getHeaterStatus() {
  String URI = "/api/v1/heater/status";
  
  if (http.begin(client, BASE_URL+URI)) {
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      if(response == "ON") {
        return 1;
      } else {
        return 0;
      }
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
  return 0;
}

int getLightStatus() {
  String URI = "/api/v1/light/status";
  
  if (http.begin(client, BASE_URL+URI)) {
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      if(response == "ON") {
        return 1;
      } else {
        return 0;
      }
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
  return 0;
}

int getMotorStatus() {
  String URI = "/api/v1/motor/status";
  
  if (http.begin(client, BASE_URL+URI)) {
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      if(response == "ON") {
        return 1;
      } else {
        return 0;
      }
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
  return 0;
}

int getLightIntensity() {
  String URI = "/api/v1/light/intensity";
  
  if (http.begin(client, BASE_URL+URI)) {
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      return response.toInt();
    }

    http.end();
  } else {
    Serial.println("[HTTP] Unable to connect");
  }
  return 0;
} 

