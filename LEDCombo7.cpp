// LEDCombo7.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo7.h"
#include "LEDSpiral.h"
#include "LEDTide.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo7 Combo7;
extern LEDSpiral Spiral;
extern LEDTide Tide;

LEDCombo7::LEDCombo7() {

}

int LEDCombo7::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo7::StartCombo7() {
	Spiral.StartSpiral();
	Tide.StartTide();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo7::StepCombo7() {
	Spiral.StepSpiral();
	Tide.StepTide();
}

