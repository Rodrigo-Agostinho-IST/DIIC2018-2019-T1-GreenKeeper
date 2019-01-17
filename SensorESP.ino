#include<SoftwareSerial.h> 
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include "AdafruitIO_WiFi.h"
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

#define IO_USERNAME    "rodrigoagostinhotecnico"
#define IO_KEY         "fb9462765fdb4368b841393c3c9adf52"

#define WIFI_SSID       "iRodrigo"
#define WIFI_PASS       "iphonerodrigo"
//#define WIFI_SSID       "ZON-6140"
//#define WIFI_PASS       "a16e3d64a49a"

#define ONE_WIRE_BUS 2

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
AdafruitIO_Feed *command = io.feed("Moisture Sensor");
AdafruitIO_Feed *command2 = io.feed("Temperature Sensor");

void setup() {
  Serial.begin(9600);
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    delay(500);
  }
}

void loop() { 
    String data = Serial.readString();
    String newData = data.substring(0, 4);
    io.run();
    command->save(newData);
    sensors.requestTemperatures();
    float tmp = sensors.getTempCByIndex(0);
    String tmpString = String(tmp);
    command2->save(tmp);
    delay(5000);
}
