#include <Servo.h>
#include "NewPing.h"

// - MARK: Motor Definitions
extern NewPing clawSonic;
extern NewPing wallSonic;

// Claw / Arm
extern Servo leftArmServo;
extern Servo rightArmServo;
extern Servo clawServo;

// - MARK: Method Definition

// Setup
void attachServos();

// Motors
void setLeft(int s);
void setRight(int s);

// Arm
void armUp();
void armDown();

// Claw
void clawOpen();
void clawClose();

// IR
void scanIR();
void scanCandleDirection();