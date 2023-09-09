#include <SoftwareSerial.h>

#include <BH1750FVI.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0
#define DHTTYPE DHT11

#define MOTOR 7
#define HEATER 8
#define MOTOR_LED 9
#define HEATER_LED 10
#define LED_LEVEL2 11
#define LED_LEVEL1 12

DHT dht(DHTPIN, DHTTYPE);
BH1750FVI lightSensor(BH1750FVI::k_DevModeContLowRes);

SoftwareSerial nodemcu(2, 3); //TX RX

void setup() {
  Serial.begin(9600);
  nodemcu.begin(115200);

  pinMode(LED_LEVEL1, OUTPUT);
  pinMode(LED_LEVEL2, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(HEATER, OUTPUT);
  pinMode(MOTOR_LED, OUTPUT);
  pinMode(HEATER_LED, OUTPUT);

  dht.begin();
  lightSensor.begin();  
}

void loop() {
  readFromNodemcu();
  readSensorValues();
  delay(1000);
}

void readFromNodemcu() {
  if (nodemcu.available()) {
    String response = nodemcu.readString();
    response.trim();

    Serial.println(response);

    int states[3] = {0,0,0};

    int n = response.substring(0,1).toInt();
    for (int j = 0; j < 3; j++) {
        states[j] = n % 2;
        n = n / 2;
    }

    int lightIntensity = response.substring(1,2).toInt();

    changeLightState(states[2], lightIntensity);
    changeHeaterState(states[1]);
    changeMotorState(states[0]);
  }
}

void readSensorValues() {
  readHumidity();
  readTemperature();
  readLightIntensity();
}

void changeLightState(bool state, int lightIntensity) {
  if (state) {
    if(lightIntensity == 1) {
      digitalWrite(LED_LEVEL1, HIGH);
      digitalWrite(LED_LEVEL2, LOW);
    }
    if(lightIntensity == 2) {
      digitalWrite(LED_LEVEL1, HIGH);
      digitalWrite(LED_LEVEL2, HIGH);
    }
  } else {
    digitalWrite(LED_LEVEL1, LOW);
    digitalWrite(LED_LEVEL2, LOW);
  } 
}

void changeHeaterState(bool state) {
  if (state) {
    digitalWrite(HEATER, LOW);
    digitalWrite(HEATER_LED, HIGH);
  } else {
    digitalWrite(HEATER, HIGH);
    digitalWrite(HEATER_LED, LOW);
  }
}

void changeMotorState(bool state) {
  if (state) {
    digitalWrite(MOTOR, HIGH);
    digitalWrite(MOTOR_LED, HIGH);
  } else {
    digitalWrite(MOTOR, LOW);
    digitalWrite(MOTOR_LED, LOW);
  }
}

void readTemperature() {
  nodemcu.print(dht.readTemperature());
}

void readHumidity() {
  nodemcu.print(dht.readHumidity());
}

void readLightIntensity() {
  nodemcu.print(lightSensor.GetLightIntensity());  
}
