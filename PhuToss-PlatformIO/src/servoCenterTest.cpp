
 #include <Arduino.h>
 #include <Servo.h>
 #include "servoCenterTest.h"

 const int servo1Pin = 10;
 const int servo2Pin = 5;

 Servo test1Servo;
 Servo test2Servo;

 void servoCenterTestSetup() {
     Serial.begin(9600);
     test1Servo.attach(10);
     test2Servo.attach(5);
 }

 void servoCenterTest() {
    Serial.println("up");
    test1Servo.write(85); 
    test2Servo.write(95);
    delay(2000);
    Serial.println("down");
    test1Servo.write(155); 
    test2Servo.write(10);
    delay(2000);
 }