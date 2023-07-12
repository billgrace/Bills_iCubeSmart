// LEDRandomFill.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDRandomFill.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDRandomFill RandomFill;

LEDRandomFill::LEDRandomFill() {

}

int LEDRandomFill::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDRandomFill::StartRandomFill() {
	Cube.ClearImage();
    Cube.SetAnimationStepSpeedPeriodTo(random(50, 150));
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	StepTarget = 510;
}

void LEDRandomFill::StepRandomFill() {
	int XYZ;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartRandomFill();
	}
	XYZ = Cube.RandomPositionWhereLEDIs(Off);
	if (XYZ == -1) {
		StartRandomFill();
	}
	Cube.SetLEDColor(Cube.XPartOf(XYZ), Cube.YPartOf(XYZ), Cube.ZPartOf(XYZ), Cube.RandomColor(), Cube.RandomColor(), Cube.RandomColor());
}
