// LEDCombo10.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo10.h"
#include "LEDJumpRope.h"
#include "LEDWorms.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo10 Combo10;
extern LEDJumpRope JumpRope;
extern LEDWorms Worms;

LEDCombo10::LEDCombo10() {

}

int LEDCombo10::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo10::StartCombo10() {
	JumpRope.StartJumpRope();
	Worms.StartWorms();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo10::StepCombo10() {
	JumpRope.StepJumpRope();
	Worms.StepWorms();
}

