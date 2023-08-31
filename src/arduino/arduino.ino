#include <SoftwareSerial.h>

#include <BH1750FVI.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0
#define DHTTYPE DHT11

#define LED1 12
#define LED2 10

#define MOTOR 8

DHT dht(DHTPIN, DHTTYPE);
BH1750FVI lightSensor(BH1750FVI::k_DevModeContLowRes);

SoftwareSerial nodemcu(2,3); //TX RX

enum LED_HEATER_MOTOR {
  OFF_OFF_OFF = 0,
  OFF_OFF_ON = 1,
  OFF_ON_OFF = 2,
  OFF_ON_ON = 3,
  ON_OFF_OFF = 4,
  ON_OFF_ON = 5,
  ON_ON_OFF = 6,
  ON_ON_ON =  7
};

void setup() {
  Serial.begin(9600);
  nodemcu.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(MOTOR, OUTPUT);

  dht.begin();
  lightSensor.begin();  
}

void loop() {
  // readFromNodemcu();
  readSensorValues();
  delay(1000);
}

void readFromNodemcu() {
  if (nodemcu.available()) {
    String response = nodemcu.readString();
    response.trim();
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
  Serial.println();
}

void changeLightState(bool state, int lightIntensity) {
  if (state) {
    if(lightIntensity == 1) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
    }
    if(lightIntensity == 2) {
      digitalWrite(LED2, HIGH);
      digitalWrite(LED1, HIGH);
    }
  } else {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
  } 
}

void changeHeaterState(bool state) {
}

void changeMotorState(bool state) {
  if(state) {
    digitalWrite(MOTOR, HIGH);
  } else {
    digitalWrite(MOTOR, LOW);
  }
}

void readTemperature() {
  Serial.print(dht.readTemperature());
}

void readHumidity() {
  Serial.print(dht.readHumidity());
}

void readLightIntensity() {
  Serial.print(lightSensor.GetLightIntensity());
}
