// LEDCombo8.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo8.h"
#include "LEDLightning.h"
#include "LEDTide.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo8 Combo8;
extern LEDLightning Lightning;
extern LEDTide Tide;

LEDCombo8::LEDCombo8() {

}

int LEDCombo8::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo8::StartCombo8() {
	Lightning.StartLightning();
	Tide.StartTide();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo8::StepCombo8() {
	Lightning.StepLightning();
	Tide.StepTide();
}

