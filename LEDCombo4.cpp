// LEDCombo4.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo4.h"
#include "LEDDash.h"
#include "LEDMarathon.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo4 Combo4;
extern LEDDash Dash;
extern LEDMarathon Marathon;

LEDCombo4::LEDCombo4() {

}

int LEDCombo4::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo4::StartCombo4() {
	Dash.StartDash();
	Marathon.StartMarathon();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo4::StepCombo4() {
	Dash.StepDash();
	Marathon.StepMarathon();
}

