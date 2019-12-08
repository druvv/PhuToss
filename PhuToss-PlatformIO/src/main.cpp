#include <Arduino.h>
#include <Servo.h>
#include "NewPing.h"

#include "main.h"
#include "tests.h"
#include "pins.h"

// Ultrasonic
NewPing clawSonic(clawSonicTrig, clawSonicEcho, 100);
NewPing wallSonic(wallSonicTrig, wallSonicEcho, 100);

// Claw / Arm
Servo leftArmServo;
Servo rightArmServo;
Servo clawServo;

// IR
enum CandleDirection { candle_none, candle_left, candle_center, candle_right };
CandleDirection candleDirection = candle_none;
int IR1 = 0;
int IR2 = 0;
int IR3 = 0;
int IR4 = 0;
int IR5 = 0;
// For any pin, when should we detect that a candle is within our sight?
const int CANDLE_DETECT_THRESHOLD = 500;

// Program Functionality
char *ProgramTypes[] =
{
    "cube_finding",
    "cube_grabbing",
    "wall_detecting",
    "cube_tossing"
};
ProgramMode programMode = cube_finding;

unsigned long CUBE_DETECT_THRESHOLD = 60;
unsigned long clawSonicDistance = 10000;
unsigned long wallSonicDistance = 10000;

unsigned long currTime = 0;

const int turnSpeed = 110;

// false - CCW, true - CW
bool scanDirectionCW = false;
unsigned long lastScanDirectionChange = 0;
unsigned long lastCubeFound = 0;
unsigned long SCAN_DIRECTION_TIMEOUT = 300; // How long the bot scans in a certain direction from the start
unsigned long LOST_CUBE_TIMEOUT = 10000; // 10s

// CUBE - GRABBING
bool firstScan = true;

/*

Timer Usage:
- Servos - Timer 5
- NewPing - Timer 2

https://www.arduino.cc/en/Main/arduinoBoardMega/
https://oscarliang.com/arduino-timer-and-interrupt-tutorial/ (see PWM and timer section)
*/


// -- MARK: FUNCTION IMPLEMENTATION

void setup() {
  attachServos();
  pinMode(wallSwitchPin, INPUT_PULLUP);
  Serial.begin(9600);

  delay(5000);
} 

// void loop() {
//   driveTrainTest();
// }

void loop() {

  currTime = millis();

  if (programMode == cube_finding) {
    Serial.println("Finding cube");
    armDown();
    clawOpen();
    scanDistances();
    // Turn slowly CCW slowly until we detect a cube
    setLeft(-turnSpeed);
    setRight(turnSpeed);

    if (clawSonicDistance < CUBE_DETECT_THRESHOLD) {
      switchProgramMode(cube_grabbing);
      return;
    }
  }

  if (programMode == cube_grabbing) {
    scanDistances();

    if (clawSonicDistance < CUBE_DETECT_THRESHOLD) {
      // Reset scanning timing stuff
      firstScan = true;
      lastScanDirectionChange = currTime;
      scanDirectionCW = true;

      lastCubeFound = currTime;

      Serial.println("Found cube");
      // Move forward slowly while we detect the cube
      setLeft(turnSpeed);
      setRight(turnSpeed);
      if (clawSonicDistance < 10) {
        Serial.println("Grabbing cube");
        // Move forward a little more
        setLeft(turnSpeed);
        setRight(turnSpeed);
        delay(250);
        setLeft(0);
        setRight(0);
        delay(1000);
        clawClose();
        delay(2000);
        armUp();
        switchProgramMode(wall_detecting);
      }
    } else {
      Serial.println("Lost cube");

      if (currTime - lastCubeFound > LOST_CUBE_TIMEOUT) {
        switchProgramMode(cube_finding);
        return;
      }

      if (firstScan && (currTime - lastScanDirectionChange) > SCAN_DIRECTION_TIMEOUT) {
        // On the first scan, only move 50% away from center.
        firstScan = false;
        lastScanDirectionChange = currTime;
        scanDirectionCW = !scanDirectionCW;
      } else if ((currTime - lastScanDirectionChange) > SCAN_DIRECTION_TIMEOUT * 2) {
        // On successive scans, move the entire distance to scan the entire range from one direction.
        lastScanDirectionChange = currTime;
        scanDirectionCW = !scanDirectionCW;
      }

      if (scanDirectionCW) {
        setLeft(turnSpeed);
        setRight(-turnSpeed);
      } else { 
        setLeft(-turnSpeed);
        setRight(turnSpeed);
      }
    }
  }

  if (programMode == wall_detecting) {
    // Spin once, drop cube

    setLeft(-turnSpeed);
    setRight(turnSpeed);
    delay(2000);

    setLeft(0);
    setRight(0);
    delay(250);

    clawOpen();

    switchProgramMode(cube_tossing);
  }

  if (programMode == cube_tossing) {
    // Do nothing
    delay(1000);
  }
}

void switchProgramMode(ProgramMode mode) {
  char buffer[50];
  sprintf(buffer, "PROGRAM MODE: %s", ProgramTypes[mode]);
  Serial.println(buffer);
  programMode = mode;
}

void attachServos() {
  leftArmServo.attach(leftArmServoPin);
  rightArmServo.attach(rightArmServoPin);
  clawServo.attach(clawServoPin);
  armDown();
  clawOpen();
}

// Arm

void armDown() {
  leftArmServo.write(10); // TODO: Test whether test1Servo refers to left or right
  rightArmServo.write(155);
}

void armUp() {
  leftArmServo.write(130); 
  rightArmServo.write(55);
}

// Claw

void clawOpen() {
  clawServo.write(80);
}

void clawClose() {
  clawServo.write(25);
}

// Motors

void setLeft(int s) {
  if (s > 0) {
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, HIGH);
  } else if (s < 0) {
    digitalWrite(motorLeftA, HIGH);
    digitalWrite(motorLeftB, LOW);
  } else {
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);
  }

  s = abs(s);
  analogWrite(motorLeftPWM, s);
}

void setRight(int s) {
  if (s > 0) {
    digitalWrite(motorRightA, HIGH);
    digitalWrite(motorRightB, LOW);
  } else if (s < 0)  {
    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, HIGH);
  } else {
    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, LOW);
  }

  s = abs(s);
  analogWrite(motorRightPWM, s);
}

// Ultrasonic

void scanDistances() {

  clawSonicDistance = clawSonic.ping_cm();
  delay(30);
  wallSonicDistance = wallSonic.ping_cm();

  if (clawSonicDistance == 0) {
    clawSonicDistance = 10000;
  }

  if (wallSonicDistance == 0) {
    wallSonicDistance = 10000;
  }
}

// Wall Switch

bool isTouchingWall() {
  return digitalRead(wallSwitchPin) == LOW;
}


// IR 

void scanIR() {
    IR1 = analogRead(IRA1_PIN);
    IR2 = analogRead(IRA2_PIN);
    IR3 = analogRead(IRA3_PIN);
    IR4 = analogRead(IRA4_PIN);
    IR5 = analogRead(IRA5_PIN);
}

/*
       IR3
   IR2     IR4
IR1           IR5
*/

void scanCandleDirection() {
  scanIR();
  int leftSum = IR1 + IR2 + IR3;
  int centerSum = IR2 + IR3 + IR4;
  int rightSum = IR3 + IR4 + IR5;

  if (leftSum < CANDLE_DETECT_THRESHOLD && centerSum < CANDLE_DETECT_THRESHOLD && rightSum < CANDLE_DETECT_THRESHOLD) {
    candleDirection = candle_none;
    return;
  }

  if (IR1 < CANDLE_DETECT_THRESHOLD &&
      IR2 < CANDLE_DETECT_THRESHOLD &&
      IR3 < CANDLE_DETECT_THRESHOLD && 
      IR4 < CANDLE_DETECT_THRESHOLD &&
      IR5 < CANDLE_DETECT_THRESHOLD) {
        candleDirection = candle_none;
        return;
      }

  // IR1 is the greatest so left
  if (IR1 > IR2 && IR1 > IR3 && IR1 > IR4 && IR1 > IR5) {
    candleDirection = candle_left;
  } else if (IR2 > IR1 && IR2 > IR3 && IR2 > IR4 && IR2 > IR5) {
    // IR2 is the greatest so left
    candleDirection = candle_left;
  } else if (IR3 > IR1 && IR3 > IR2 && IR3 > IR4 && IR3 > IR5) {
    // IR3 is the greatest so center
    candleDirection = candle_center;
  } else if (IR4 > IR1 && IR4 > IR2 && IR4 > IR3 && IR4 > IR5) {
    // IR4 is the greatest so right
    candleDirection = candle_right;
  } else if (IR5 > IR1 && IR5 > IR2 && IR5 > IR3 && IR5 > IR4) {
    // IR5 is the greatest so right
    candleDirection = candle_right;
  }
}