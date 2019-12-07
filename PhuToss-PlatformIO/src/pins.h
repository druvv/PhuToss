#include <Arduino.h>

// Motors
const int motorRightPWM = 51;
const int motorRightA = 47;
const int motorRightB = 49;

const int motorLeftPWM = 41;
const int motorLeftA = 43;
const int motorLeftB = 45;

// Ultrasonic
const int clawSonicTrig = 13;
const int clawSonicEcho = 12;

const int wallSonicTrig = 50;
const int wallSonicEcho = 48;

// Claw / Arm
const int clawServoPin = 5;
const int leftArmServoPin = 31;
const int rightArmServoPin = 3;

// IR
const int IRA1_PIN = A0;
const int IRA2_PIN = A1;
const int IRA3_PIN = A2;
const int IRA4_PIN = A3;
const int IRA5_PIN = A4;