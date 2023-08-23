// LEDBigSlosh.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDBigSlosh.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDBigSlosh BigSlosh;

LEDBigSlosh::LEDBigSlosh() {

}

int LEDBigSlosh::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDBigSlosh::StartBigSlosh() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
}

void LEDBigSlosh::StepBigSlosh() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartBigSlosh();
	}
}
