#include "NewPing.h"

// Ultrasonic for testing
extern NewPing clawSonic;
extern NewPing wallSonic;

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

// Wall Switch
bool isTouchingWall();

// IR
void scanIR();
void scanCandleDirection();