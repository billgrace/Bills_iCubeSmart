// LEDLightning.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDLightning.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDLightning Lightning;

LEDLightning::LEDLightning () {

}

int LEDLightning::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDLightning::StartLightning() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	// Run a fast interrupt cycle
	Cube.SetAnimationStepSpeedPeriodTo(random(2, 5));
	StepCounter = 0;
	StepTarget = random(1000, 2000);
	StrikeCounter = 0;
	StrikeTarget = random(50, 130);
}

void LEDLightning::StepLightning() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartLightning();
	}
	// Keep a gray sky roiling
	GrayLevel = random(1, 5);
	Cube.SetLEDColor(random(0, 8), random(0, 8), 7, GrayLevel, GrayLevel, GrayLevel);
	// Time to start a lightning strike?
	StrikeCounter++;
	if (StrikeCounter >= StrikeTarget) {
		StrikeCounter = 0;
		StrikeTarget = random(50, 130);
		StartStrike();
	}
	// If there's a strike active, move it another notch along
	StepStrike();
}

void LEDLightning::StartStrike() {
	StrikeActive = true;
	StrikeX = random(0, 8);
	StrikeY = random(0, 8);
	StrikeZ = 6;
}

void LEDLightning::StepStrike() {
	if (StrikeActive) {
		if (StrikeZ == 0) {
			// This strike has reached the ground... erase it
			for (int i = 0; i < 7; i++) {
				Cube.SetLEDColor(StrikeX, StrikeY, i, 0, 0, 0);
			}
			// ... and mark it no longer active
			StrikeActive = false;
		} else {
			// This strike is still descending
			Cube.SetLEDColor(StrikeX, StrikeY, StrikeZ, 7, 7, 7);
			StrikeZ--;
		}
	}
}
