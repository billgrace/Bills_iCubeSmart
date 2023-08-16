// LEDSheets.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDSheets.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDSheets Sheets;

LEDSheets::LEDSheets() {

}

int LEDSheets::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDSheets::StartSheets() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	StepTarget = random(150, 300);
	Cube.SetAnimationStepSpeedPeriodTo(random(50, 100));
	// Start all levels as empty, direction is a random filling direction
	for (int i = 0; i < 8; i++) {
		Level[i][0] = Cube.RandomColor();
		Level[i][1] = Cube.RandomColor();
		Level[i][2] = Cube.RandomColor();
		Level[i][3] = 0;
		Level[i][4] = random(0, 4);
	}
	CurrentLevel = random(0, 8);
}

void LEDSheets::StepSheets() {
	int X;
	int Y;
	int Z;
	int Red;
	int Green;
	int Blue;
	int OldLength;
	int NewLength;
	bool TimeToChangeLevel = false;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartSheets();
	}
	// Is the current level done?
	if (Level[CurrentLevel][4] < 4) {
		// The current level is filling
		if (Level[CurrentLevel][3] >= 8) {
			TimeToChangeLevel = true;
		}
	} else {
		// The current level is emptying
		if (Level[CurrentLevel][3] <= 0) {
			TimeToChangeLevel = true;
		}
	}
	if (TimeToChangeLevel == true) {
		// Pick a new level
		CurrentLevel = Cube.RandomButDifferent(CurrentLevel, 0, 8);
		// If the new level is full, set it to an emptying direction & vice versa
		if (Level[CurrentLevel][3] < 4) {
			// The new level is more empty than full (actually *SHOULD* be only 0 or 8)
			Level[CurrentLevel][4] = random(0, 4);
			Level[CurrentLevel][3] = 0;
		} else {
			// The new level is (more) full
			Level[CurrentLevel][4] = random(4, 8);
			Level[CurrentLevel][3] = 8;
		}
	}
	// OK, we've established the level, direction and length so add or erase one row
	Z = CurrentLevel;
	Red = Level[CurrentLevel][0];
	Green = Level[CurrentLevel][1];
	Blue = Level[CurrentLevel][2];
	OldLength = Level[CurrentLevel][3];
	switch (Level[CurrentLevel][4]) {
	case 0:
		// Filling left to right
		X = OldLength;
		for (Y = 0; Y < 8; Y++) {
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		}
		NewLength = OldLength + 1;
		break;
	case 1:
		// Filling right to left
		X = 7 - OldLength;
		for (Y = 0; Y < 8; Y++) {
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		}
		NewLength = OldLength + 1;
		break;
	case 2:
		// Filling front to back
		Y = OldLength;
		for (X = 0; X < 8; X++) {
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		}
		NewLength = OldLength + 1;
		break;
	case 3:
		// Filling back to front
		Y = 7 - OldLength;
		for (X = 0; X < 8; X++) {
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		}
		NewLength = OldLength + 1;
		break;
	case 4:
		// Emptying right to left
		X = OldLength - 1;
		for (Y = 0; Y < 8; Y++) {
			Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
		}
		NewLength = OldLength - 1;
		break;
	case 5:
		// Emptying left to right
		X = 8 - OldLength;
		for (Y = 0; Y < 8; Y++) {
			Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
		}
		NewLength = OldLength - 1;
		break;
	case 6:
		// Emptying back to front
		Y = OldLength - 1;
		for (X = 0; X < 8; X++) {
			Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
		}
		NewLength = OldLength - 1;
		break;
	case 7:
		// Emptying front to back
		Y = 8 - OldLength;
		for (X = 0; X < 8; X++) {
			Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
		}
		NewLength = OldLength - 1;
		break;
	}
	Level[CurrentLevel][3] = NewLength;
}
