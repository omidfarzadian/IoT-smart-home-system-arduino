#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <SoftwareSerial.h>

#define BASE_URL "http://192.168.1.98:2500"

#define SSID "Lord of the Pings"
#define PASS "7XYSKDAY"

SoftwareSerial arduino(2, 3);

WiFiClient client;
HTTPClient http;

void setup() {

  Serial.begin(115200);
  arduino.begin(9600);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    readDataFromArduino();
  }

  delay(1000);
}

void readDataFromArduino() {
  if (arduino.available()) {
     String data = arduino.readString();
     data.trim();
     
    String humidity = data.substring(0, 4);
    String temperature = data.substring(5, 9);
    String intensity = data.substring(10, 11);

    sendHumidityData(humidity);
    sendTemperatureData(temperature);
    sendLightIntensityData(intensity);
  }
}

void sendHumidityData(String humidity) {
  String URI = "/api/v1/humidity/change/";
  http.begin(client, BASE_URL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST("{Humidity:" + humidity + "}");

  if (httpCode > 0 && httpCode == HTTP_CODE_OK ) {
    const String& payload = http.getString();
  }

  http.end();
}

void sendTemperatureData(String temperature) {
  String URI = "/api/v1/temperature/change/";
  http.begin(client, BASE_URL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST("{Temperature:" + temperature + "}");

  if (httpCode > 0 && httpCode == HTTP_CODE_OK ) {
    const String& payload = http.getString();
  }

  http.end();
}

void sendLightIntensityData(String intensity) {
  String URI = "/api/v1/light/change/";
  http.begin(client, BASE_URL);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST("{Intensity:" + intensity + "}");

  if (httpCode > 0 && httpCode == HTTP_CODE_OK ) {
    const String& payload = http.getString();
  }

  http.end();
}
