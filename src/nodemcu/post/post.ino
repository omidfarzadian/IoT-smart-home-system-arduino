/**
   PostHTTPClient.ino

    Created on: 21.11.2016

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <SoftwareSerial.h>

#define BASE_URL "http://192.168.1.126:2501"

#define SSID "Kav"
#define PASS "33457043"

SoftwareSerial arduino(2, 3);

WiFiClient client;
HTTPClient http;

void setup() {

  Serial.begin(230400);
  arduino.begin(9600);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {


    // Serial.print("[HTTP] begin...\n");
    // // configure traged server and url
    // http.begin(client, "http://" SERVER_IP "/postplain/");  // HTTP
    // http.addHeader("Content-Type", "application/json");

    // Serial.print("[HTTP] POST...\n");
    // // start connection and send HTTP header and body
    // int httpCode = http.POST("{\"hello\":\"world\"}");

    // // httpCode will be negative on error
    // if (httpCode > 0) {
    //   // HTTP header has been send and Server response header has been handled
    //   Serial.printf("[HTTP] POST... code: %d\n", httpCode);

    //   // file found at server
    //   if (httpCode == HTTP_CODE_OK) {
    //     const String& payload = http.getString();
    //     Serial.println("received payload:\n<<");
    //     Serial.println(payload);
    //     Serial.println(">>");
    //   }
    // } else {
    //   Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    // }

    // http.end();

    sendHumidityData();
  }

  delay(1000);
}

void sendHumidityData() {
  http.begin(client, BASE_URL "/api/v1/humidity/change/");  // HTTP
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.POST("{\"Humidity\":\"28.7\"}");

  if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}
