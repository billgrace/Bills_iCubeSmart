// LEDWireCube.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDWireCube.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDWireCube WireCube;

LEDWireCube::LEDWireCube() {

}

int LEDWireCube::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDWireCube::StartWireCube() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(250, 350));
	StepCounter = 0;
	StepTarget = random(30, 100);
	ColorChangeCounter = 0;
	ColorChangeTarget = random(5, 25);
	EdgeLength = 2;
	EdgeLengthDelta = 1;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
}

void LEDWireCube::StepWireCube() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartWireCube();
	}
	ColorChangeCounter++;
	if (ColorChangeCounter >= ColorChangeTarget) {
		ColorChangeCounter = 0;
		Red = Cube.RandomColor();
		Green = Cube.RandomColor();
		Blue = Cube.RandomColor();
	}
	// Erase previous
	DrawCube(true);
	// Adjust size
	if (EdgeLengthDelta > 0) {
		// Size is growing
		if (EdgeLength == 8) {
			// Size is max so turn around
			EdgeLength -= 2;
			EdgeLengthDelta = -1;
		} else {
			// Still room to grow
			EdgeLength += 2;
		}
	} else {
		// Size is shrinking
		if (EdgeLength == 2) {
			// Size is min so turn around
			EdgeLength += 2;
			EdgeLengthDelta = 1;
		} else {
			// Still room to shrink
			EdgeLength -= 2;
		}
	}
	// Draw new
	DrawCube(false);
}

void LEDWireCube::DrawCube(bool Erase) {
	int C1;
	int C2;
	int X;
	int Y;
	int Z;
	int R;
	int G;
	int B;
	if (Erase) {
		R = 0;
		G = 0;
		B = 0;
	} else {
		R = Red;
		G = Green;
		B = Blue;
	}
	switch (EdgeLength) {
	case 2:
		C1 = 3;
		C2 = 4;
		break;
	case 4:
		C1 = 2;
		C2 = 5;
		break;
	case 6:
		C1 = 1;
		C2 = 6;
		break;
	case 8:
		C1 = 0;
		C2 = 7;
		break;
	}
	for (X = C1; X <= C2; X++) {
		Cube.SetLEDColor(X, C1, C1, R, G, B);
		Cube.SetLEDColor(X, C1, C2, R, G, B);
		Cube.SetLEDColor(X, C2, C1, R, G, B);
		Cube.SetLEDColor(X, C2, C2, R, G, B);
	}
	for (Y = C1; Y <= C2; Y++) {
		Cube.SetLEDColor(C1, Y, C1, R, G, B);
		Cube.SetLEDColor(C1, Y, C2, R, G, B);
		Cube.SetLEDColor(C2, Y, C1, R, G, B);
		Cube.SetLEDColor(C2, Y, C2, R, G, B);
	}
	for (Z = C1; Z <= C2; Z++) {
		Cube.SetLEDColor(C1, C1, Z, R, G, B);
		Cube.SetLEDColor(C1, C2, Z, R, G, B);
		Cube.SetLEDColor(C2, C1, Z, R, G, B);
		Cube.SetLEDColor(C2, C2, Z, R, G, B);
	}
}
