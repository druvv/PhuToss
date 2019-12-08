#include "NewPing.h"

// Ultrasonic for testing
extern NewPing clawSonic;
extern NewPing wallSonic;

enum ProgramMode { cube_finding, cube_grabbing, wall_detecting, cube_tossing };

// - MARK: Method Definition

// Setup
void attachServos();

// Program Mode
void switchProgramMode(ProgramMode);

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

// Ultrasonic
void scanDistances();

// IR
void scanIR();
void scanCandleDirection();