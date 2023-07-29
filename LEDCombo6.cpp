// LEDCombo6.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo6.h"
#include "LEDMerryGoRound.h"
#include "LEDRadar.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo6 Combo6;
extern LEDMerryGoRound MerryGoRound;
extern LEDRadar Radar;

LEDCombo6::LEDCombo6() {

}

int LEDCombo6::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo6::StartCombo6() {
	MerryGoRound.StartMerryGoRound();
	Radar.StartRadar();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo6::StepCombo6() {
	MerryGoRound.StepMerryGoRound();
	Radar.StepRadar();
}

