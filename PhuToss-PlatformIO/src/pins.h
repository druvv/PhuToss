#include <Arduino.h>

// Motors
const int motorRightPWM = 40;
const int motorRightA = 42;
const int motorRightB = 44;

const int motorLeftPWM = 50;
const int motorLeftA = 46;
const int motorLeftB = 48;

// Ultrasonic
const int clawSonicTrig = 13;
const int clawSonicEcho = 12;

const int wallSonicTrig = 8;
const int wallSonicEcho = 9;

// Claw / Arm
const int clawServoPin = 5;
const int leftArmServoPin = 31;
const int rightArmServoPin = 3;

// Back Switch
const int wallSwitchPin = 52;

// IR
const int IRA1_PIN = A0;
const int IRA2_PIN = A1;
const int IRA3_PIN = A2;
const int IRA4_PIN = A3;
const int IRA5_PIN = A4;