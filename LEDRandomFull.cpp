// LEDRandomFull.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDRandomFull.h"

extern LEDCube Cube;
extern LEDRandomFull RandomFull;

LEDRandomFull::LEDRandomFull() {

}

int LEDRandomFull::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDRandomFull::StartRandomFull() {
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(3, 10));
	MaxNumberOfSteps = random(1000, 3000);
	StepCount = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			for (int z = 0; z < 8; z++) {
				Cube.SetLEDColor(x, y, z, Cube.RandomColor(), Cube.RandomColor(), Cube.RandomColor());
			}
		}
	}
}

void LEDRandomFull::StepRandomFull() {
	Cube.SetLEDColor(random(0, 8), random(0, 8), random(0, 8), Cube.RandomColor(), Cube.RandomColor(), Cube.RandomColor());
	StepCount++;
	if (StepCount >= MaxNumberOfSteps) {
		StartRandomFull();
	}
}
