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

#define MOTOR_PIN 12
int state = 1;

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *command = io.feed("Motor Boolean");

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  io.connect();
  command->onMessage(handleMessage);
  //command->get();
  while (io.status() < AIO_CONNECTED) {
    Serial.println("Not connected");
    delay(500);
  }
}

void loop() { 
    io.run();
    if(state == 1){
       digitalWrite(MOTOR_PIN, HIGH);
    } else {
       digitalWrite(MOTOR_PIN, LOW);
    }
}

void handleMessage(AdafruitIO_Data *data) {
  String dataReceived = data->toString();
  if (dataReceived == "ON"){
    Serial.println("Motor ON");
    state = 1;
  } else if (dataReceived == "OFF"){
    Serial.println("Motor OFF");
    state = 0;
  }
}
