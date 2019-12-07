#include <Arduino.h>
#include "RemoteDebug.h"
#include <WiFi.h>
#include <HardwareSerial.h>

RemoteDebug Debug;

HardwareSerial arduinoSerial(1);

// Replace with your network credentials
const char* ssid     = "ESP32-PhuToss";
const char* password = "PhuToss-DhruvSringari";

unsigned long curr_time = 0;
unsigned long lastPing = 0;

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600, SERIAL_8N1, 39, 19);
  // put your setup code here, to run once:
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  Debug.begin("192.168.4.1");
}

void loop() {

  while (arduinoSerial.available() > 0) {
    String s = arduinoSerial.readStringUntil('\n');
    debugA("%s", s.c_str());
  }

  Debug.handle();
}