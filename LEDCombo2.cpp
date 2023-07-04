// LEDCombo2.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo2.h"
#include "LEDDash.h"
#include "LEDBall.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo2 Combo2;
extern LEDDash Dash;
extern LEDBall Ball;

LEDCombo2::LEDCombo2() {

}

int LEDCombo2::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo2::StartCombo2() {
	Dash.StartDash();
	Ball.StartBall();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo2::StepCombo2() {
	Dash.StepDash();
	Ball.StepBall();
}