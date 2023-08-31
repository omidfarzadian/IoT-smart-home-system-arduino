#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define SSID "Lord of the Pings"
#define PASS "7YWSKDAY"

#define BASE_URL "http://37.152.163.82:2500"

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

    readDataFromArduino();
  }
  delay(2000);
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
  }
  return 0;
}

int getLightIntensity() {
  String URI = "/api/v1/light/level";
  
  if (http.begin(client, BASE_URL+URI)) {
    int httpCode = http.GET();
    
    if (httpCode == HTTP_CODE_OK) {
      String response = http.getString();
      return response.toInt();
    }

    http.end();
  }
  return 0;
} 


void readDataFromArduino() {
  String data = Serial.readString();
  data.trim();
     
  String humidity = data.substring(0, 4);
  String temperature = data.substring(5, 9);
  String intensity = data.substring(10, 12);
  
  sendHumidityData(humidity);
  sendTemperatureData(temperature);
  sendLightIntensityData(intensity);
}

void sendHumidityData(String humidity) {
  String URI = "/api/v1/humidity/change/";
  http.begin(client, BASE_URL+URI);
  http.addHeader("Content-Type", "application/json");

  String body = "{\"Humidity\":\"" + humidity + "\"}";
  int httpCode = http.POST(body);

  if (httpCode > 0 && httpCode == HTTP_CODE_OK ) {
    const String& payload = http.getString();
  }

  http.end();
}

void sendTemperatureData(String temperature) {
  String URI = "/api/v1/temperature/change/";
  http.begin(client, BASE_URL+URI);
  http.addHeader("Content-Type", "application/json");

  String body = "{\"Temperature\":\"" + temperature + "\"}";
  int httpCode = http.POST(body);

  if (httpCode > 0 && httpCode == HTTP_CODE_OK ) {
    const String& payload = http.getString();
  }

  http.end();
}

void sendLightIntensityData(String intensity) {
  String URI = "/api/v1/light/changeIntensity";
  http.begin(client, BASE_URL+URI);
  http.addHeader("Content-Type", "application/json");

  String body = "{\"Intensity\":\"" + intensity + "\"}";
  int httpCode = http.POST(body);

  if (httpCode > 0 && httpCode == HTTP_CODE_OK ) {
    const String& payload = http.getString();
  }

  http.end();
}
