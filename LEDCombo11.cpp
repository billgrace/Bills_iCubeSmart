// LEDCombo11.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo11.h"
#include "LEDFlopWall.h"
#include "LEDJumpRope.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo11 Combo11;
extern LEDFlopWall FlopWall;
extern LEDJumpRope JumpRope;

LEDCombo11::LEDCombo11() {

}

int LEDCombo11::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo11::StartCombo11() {
	JumpRope.StartJumpRope();
	FlopWall.StartFlopWall();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo11::StepCombo11() {
	JumpRope.StepJumpRope();
	FlopWall.StepFlopWall();
}

