#include<SoftwareSerial.h> 
#define ANALOG_PIN A0

SoftwareSerial ESP8266WiFi(0,1);

void setup() {
  ESP8266WiFi.begin(9600);
}

void loop() {
  int sensorValue = analogRead(ANALOG_PIN);
  String sensorValueString = String(sensorValue);
  ESP8266WiFi.println(sensorValueString);
  delay(5000);
}
