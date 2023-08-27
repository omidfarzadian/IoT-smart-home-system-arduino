#include <SoftwareSerial.h>

#include <BH1750FVI.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0
#define DHTTYPE DHT11

#define LED 12

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

  pinMode(LED, OUTPUT);

  dht.begin();
  lightSensor.begin();  
}

void loop() {
  readFromNodemcu();
}

void readFromNodemcu() {
  if (nodemcu.available()) {
    String response = nodemcu.readString();
    response.trim();
    
    int states[3] = {0,0,0};

    int n = response.toInt();
    for (int j = 0; j < 3; j++) {
        states[j] = n % 2;
        n = n / 2;
    }

    changeLightState(states[0]);
    changeHeaterState(states[1]);
    changeMotorState(states[2]);
  }
}

void changeLightState(bool state) {

}

void changeHeaterState(bool state) {
  // Serial.println("UHSEIFASEUFSADF");
  if (state) {
    digitalWrite(LED, HIGH);
    // Serial.println("LED ON");
  } else {
    digitalWrite(LED, LOW);
    // Serial.println("LED OFF");
  }
}

void changeMotorState(bool state) {

}

void readTemperature() {
  Serial.print("Temperature: ");
  Serial.println(dht.readTemperature());
}

void readHumidity() {
  Serial.print("Humidity: ");
  Serial.println(dht.readHumidity());
}

void readLightIntensity() {
  Serial.print("Light Intensity: ");
  Serial.println(lightSensor.GetLightIntensity());
}

int* convertDecToBin(int n) {
    int binaryNumber[3] = {0,0,0};
    for (int j = 0; j < 3; j++) {
        binaryNumber[j] = n % 2;
        n = n / 2;
    }

    return binaryNumber;
}
