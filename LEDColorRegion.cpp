// LEDColorRegion.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDColorRegion.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDColorRegion ColorRegion;

LEDColorRegion::LEDColorRegion() {
}

int LEDColorRegion::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDColorRegion::StartColorRegion() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	CurrentX = Cube.RandomColor();
	CurrentY = Cube.RandomColor();
	CurrentZ = Cube.RandomColor();
	CurrentDeltaX = Cube.RandomDeltaPosition() * 2;
	CurrentDeltaY = Cube.RandomDeltaPosition() * 2;
	CurrentDeltaZ = Cube.RandomDeltaPosition() * 2;
	OverallStepCounter = 0;
	OverallStepTarget = random(300, 500);
	StartNewCenter();
	StartNewColor();
}

void LEDColorRegion::StepColorRegion() {
	OverallStepCounter++;
	if (OverallStepCounter >= OverallStepTarget) {
		StartColorRegion();
	} else {
		CurrentColorStepCounter++;
		if (CurrentColorStepCounter >= CurrentColorStepTarget) {
			StartNewColor();
			StartNewCenter();
		}
		AddAnLED();
	}
}

void LEDColorRegion::AddAnLED() {
	int X = Cube.NearbyCoordinate(CurrentX, 1);
	int Y = Cube.NearbyCoordinate(CurrentY, 1);
	int Z = Cube.NearbyCoordinate(CurrentZ, 1);
	Cube.SetLEDColor(X, Y, Z, CurrentRed, CurrentGreen, CurrentBlue);
}

void LEDColorRegion::StartNewColor() {
	switch(random(0, 4)) {
	case 0:
		// Small, fast
		RegionRadius = 1;
		Cube.SetAnimationStepSpeedPeriodTo(random(10, 30));
		CurrentColorStepTarget = random(30, 50);
		HoldStepTarget = random(5, 10);
		break;
	case 1:
		// Small, slow
		RegionRadius = 1;
		Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
		CurrentColorStepTarget = random(30, 50);
		HoldStepTarget = random(5, 10);
		break;
	case 2:
		// Large, fast
		RegionRadius = 2;
		Cube.SetAnimationStepSpeedPeriodTo(random(10, 30));
		CurrentColorStepTarget = random(50, 80);
		HoldStepTarget = random(5, 10);
		break;
	case 3:
		// Large slow
		RegionRadius = 2;
		Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
		CurrentColorStepTarget = random(50, 80);
		HoldStepTarget = random(5, 10);
		break;
	}
	CurrentColorStepCounter = 0;
	HoldStepCounter = 0;
	CurrentRed = Cube.RandomColor();
	CurrentGreen = Cube.RandomColor();
	CurrentBlue = Cube.RandomColor();
}

void LEDColorRegion::StartNewCenter() {
	switch(random(0, 3)) {
	case 0:
		CurrentX = CurrentX + CurrentDeltaX;
		if (CurrentX > 7) {
			CurrentX = 6;
			CurrentDeltaX = -3;
		}
		if (CurrentX < 0) {
			CurrentX = 1;
			CurrentDeltaX = 3;
		}
		break;
	case 1:
		CurrentY = CurrentY + CurrentDeltaY;
		if (CurrentY > 7) {
			CurrentY = 6;
			CurrentDeltaY = -3;
		}
		if (CurrentY < 0) {
			CurrentY = 1;
			CurrentDeltaY = 3;
		}
		break;
	case 2:
		CurrentZ = CurrentZ + CurrentDeltaZ;
		if (CurrentZ > 7) {
			CurrentZ = 6;
			CurrentDeltaZ = -3;
		}
		if (CurrentZ < 0) {
			CurrentZ = 1;
			CurrentDeltaZ = 3;
		}
		break;
	}
}