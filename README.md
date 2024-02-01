# University Bachelor Project - IoT Smart Home System

## Overview
This repository contains the Arduino for an IoT-based smart home system developed as a part of the university bachelor project. The project utilizes an Arduino Uno as the main board and a NodeMCU module for WiFi connectivity. The system incorporates various sensors and actuators to monitor and control different aspects of a smart home, such as temperature, humidity, and light.

## Components Used
- Arduino Uno
- NodeMCU module
- DHT11 sensor for temperature and humidity
- BH1750FVI sensor for light intensity
- Various LEDs for controlling light
- Relay modules for controlling the heater and fan

## Arduino
The Arduino is responsible for reading sensor values, communicating with the NodeMCU module, and controlling the connected devices based on the received commands. The code uses SoftwareSerial to communicate with the NodeMCU module and includes libraries for DHT and BH1750FVI sensors.

## NodeMCU
The NodeMCU module establishes a WiFi connection, periodically retrieves status information from the Arduino, and sends sensor data to a server via HTTP requests.

## Dependencies
- Arduino SoftwareSerial Library
- DHT Sensor Library
- BH1750FVI Light Sensor Library
- ESP8266WiFi Library
- ESP8266WiFiMulti Library
- ESP8266HTTPClient Library
