// LEDLineFill.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDLineFill.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDLineFill LineFill;

LEDLineFill::LEDLineFill () {

}

int LEDLineFill::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDLineFill::StartLineFill() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	LineCounter = 0;
	LineTarget = random(90, 150);
	StartALine();
}

void LEDLineFill::StepLineFill() {
	if (LineCounter >= LineTarget) {
		StartLineFill();
	}
	Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
	X = X + DeltaX;
	Y = Y + DeltaY;
	Z = Z + DeltaZ;
	if ((X > 7) || (X < 0) || (Y > 7) || (Y < 0) || (Z > 7) || (Z < 0)) {
		StartALine();
	}
}

void LEDLineFill::StartALine() {
	LineCounter++;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	switch (random(0, 6)) {
	case 0:
		// Starting face is +X
		X = 7;
		Y = random(0, 8);
		Z = random(0, 8);
		DeltaX = -1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 1:
		// Starting face is -X
		X = 0;
		Y = random(0, 8);
		Z = random(0, 8);
		DeltaX = 1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 2:
		// Starting face is +Y
		X = random(0, 8);
		Y = 7;
		Z = random(0, 8);
		DeltaX = 0;
		DeltaY = -1;
		DeltaZ = 0;
		break;
	case 3:
		// Starting face is -Y
		X = random(0, 8);
		Y = 0;
		Z = random(0, 8);
		DeltaX = 0;
		DeltaY = 1;
		DeltaZ = 0;
		break;
	case 4:
		// Starting face is +Z
		X = random(0, 8);
		Y = random(0, 8);
		Z = 7;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = -1;
		break;
	case 5:
		// Starting face is -Z
		X = random(0, 8);
		Y = random(0, 8);
		Z = 0;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = 1;
		break;
	}
}