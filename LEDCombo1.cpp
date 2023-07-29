// LEDCombo1.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo1.h"
#include "LEDFlopWall.h"
#include "LEDPong.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo1 Combo1;
extern LEDFlopWall FlopWall;
extern LEDPong Pong;

LEDCombo1::LEDCombo1() {

}

int LEDCombo1::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo1::StartCombo1() {
	FlopWall.StartFlopWall();
	Pong.StartPong();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo1::StepCombo1() {
	FlopWall.StepFlopWall();
	Pong.StepPong();
}

