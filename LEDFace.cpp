// LEDFace.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDFace.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDFace Face;

LEDFace::LEDFace() {

}

int LEDFace::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDFace::StartFace() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	StepCounter = 0;
	StepTarget = random(200, 500);
}

void LEDFace::StepFace() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartFace();
	}
}
