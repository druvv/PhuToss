
 #include <Arduino.h>
 #include "Servo.h"
 #include "tests.h"
 #include "main.h"

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

 void clawTest() {
    Serial.println("Testing claw open");
    clawOpen();
    delay(1000);
    Serial.println("Testing claw close");
    clawClose();
    delay(1000);
 }

  void armTest() {
    Serial.println("Testing arm up");
    armUp();
    delay(3000);
    Serial.println("Testing arm down");
    armDown();
    delay(3000);
 }

 unsigned long clawDist = 0;
 unsigned long wallDist = 0;

 void ultrasonicTest() {
      clawDist = clawSonic.ping_cm();
      delay(30);
      Serial.print("Claw Dist: "); Serial.println(clawDist);
      delay(1000);

      wallDist = wallSonic.ping_cm();
      delay(30);
      Serial.print("Wall Dist: "); Serial.println(wallDist);
      delay(1000);
 }

 void driveTrainTest() {
    Serial.println("Testing left only f");
    setLeft(255);
    setRight(0);
    delay(2000);
    Serial.println("Testing left only f slow");
    setLeft(150);
    setRight(0);
    delay(2000);
    Serial.println("Testing left only b");
    setLeft(-150);
    setRight(0);
    delay(2000);
    Serial.println("Testing right only f");
    setLeft(0);
    setRight(150);
    delay(2000);
    Serial.println("Testing right only b");
    setLeft(0);
    setRight(-150);
    delay(2000);
 }

 void wallSwitchTest() {
    if (isTouchingWall()) {
       Serial.println("Touching wall");
    } else {
       Serial.println("Not touching wall");
    }
    delay(250);
 }