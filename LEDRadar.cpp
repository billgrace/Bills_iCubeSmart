// LEDRadar.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDRadar.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDRadar Radar;

LEDRadar::LEDRadar() {

}

int LEDRadar::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDRadar::StartRadar() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	StepTarget = random(50, 100);
	Angle = random(0, 12);
	Mode = random(0, 4);
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	Cube.SetAnimationStepSpeedPeriodTo(random(50, 150));
}

void LEDRadar::StepRadar() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartRadar();
	}
	// Turn off previous beam
	DrawBeam(0, 0, 0);
	Angle++;
	if (Angle >= 12) {
		Angle = 0;
	}
	// Light up new beam
	DrawBeam(Red, Green, Blue);
}

void LEDRadar::DrawBeam(int Red, int Green, int Blue) {
	int X1;
	int Y1;
	int X2;
	int Y2;
	int X3;
	int Y3;
	int X4;
	int Y4;
	switch (Angle) {
	case 0:
		X1 = 4;
		Y1 = 4;
		X2 = 5;
		Y2 = 4;
		X3 = 6;
		Y3 = 4;
		X4 = 7;
		Y4 = 4;
		break;
	case 1:
		X1 = 4;
		Y1 = 4;
		X2 = 5;
		Y2 = 5;
		X3 = 6;
		Y3 = 6;
		X4 = 7;
		Y4 = 7;
		break;
	case 2:
		X1 = 4;
		Y1 = 4;
		X2 = 4;
		Y2 = 5;
		X3 = 4;
		Y3 = 6;
		X4 = 4;
		Y4 = 7;
		break;
	case 3:
		X1 = 3;
		Y1 = 4;
		X2 = 3;
		Y2 = 5;
		X3 = 3;
		Y3 = 6;
		X4 = 3;
		Y4 = 7;
		break;
	case 4:
		X1 = 3;
		Y1 = 4;
		X2 = 2;
		Y2 = 5;
		X3 = 1;
		Y3 = 6;
		X4 = 0;
		Y4 = 7;
		break;
	case 5:
		X1 = 3;
		Y1 = 4;
		X2 = 2;
		Y2 = 4;
		X3 = 1;
		Y3 = 4;
		X4 = 0;
		Y4 = 4;
		break;
	case 6:
		X1 = 3;
		Y1 = 3;
		X2 = 2;
		Y2 = 3;
		X3 = 1;
		Y3 = 3;
		X4 = 0;
		Y4 = 3;
		break;
	case 7:
		X1 = 3;
		Y1 = 3;
		X2 = 2;
		Y2 = 2;
		X3 = 1;
		Y3 = 1;
		X4 = 0;
		Y4 = 0;
		break;
	case 8:
		X1 = 3;
		Y1 = 3;
		X2 = 3;
		Y2 = 2;
		X3 = 3;
		Y3 = 1;
		X4 = 3;
		Y4 = 0;
		break;
	case 9:
		X1 = 4;
		Y1 = 3;
		X2 = 4;
		Y2 = 2;
		X3 = 4;
		Y3 = 1;
		X4 = 4;
		Y4 = 0;
		break;
	case 10:
		X1 = 4;
		Y1 = 3;
		X2 = 5;
		Y2 = 2;
		X3 = 6;
		Y3 = 1;
		X4 = 7;
		Y4 = 0;
		break;
	case 11:
		X1 = 4;
		Y1 = 3;
		X2 = 5;
		Y2 = 3;
		X3 = 6;
		Y3 = 3;
		X4 = 7;
		Y4 = 3;
		break;
	}
	DrawVertical(1, X1, Y1, Red, Green, Blue);
	DrawVertical(2, X2, Y2, Red, Green, Blue);
	DrawVertical(3, X3, Y3, Red, Green, Blue);
	DrawVertical(4, X4, Y4, Red, Green, Blue);
}

void LEDRadar::DrawVertical(int Radius, int X, int Y, int Red, int Green, int Blue) {
	int Z0;
	int Z1;
	int Z2;
	switch (Radius) {
	case 1:
		Z1 = 3;
		Z2 = 4;
		break;
	case 2:
		Z1 = 2;
		Z2 = 5;
		break;
	case 3:
		Z1 = 1;
		Z2 = 6;
		break;
	case 4:
		Z1 = 0;
		Z2 = 7;
		break;
	}
	switch (Mode) {
	case 0:
		// solid rectangle
		for (Z0 = 0; Z0 < 8; Z0++) {
			Cube.SetLEDColor(X, Y, Z0, Red, Green, Blue);
		}
		break;
	case 1:
		// solid "triangle"
		for (Z0 = Z1; Z0 <= Z2; Z0++) {
			Cube.SetLEDColor(X, Y, Z0, Red, Green, Blue);
		}
		break;
	case 2:
		// outline rectangle
		if ((Radius == 1) || (Radius == 4)) {
			for (Z0 = 0; Z0 < 8; Z0++) {
				Cube.SetLEDColor(X, Y, Z0, Red, Green, Blue);
			}
		} else {
			Cube.SetLEDColor(X, Y, 0, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, 7, Red, Green, Blue);
		}
		break;
	case 3:
		// outline "triangle"
		if (Radius == 4) {
			for (Z0 = 0; Z0 < 8; Z0++) {
				Cube.SetLEDColor(X, Y, Z0, Red, Green, Blue);
			}
		} else {
			Cube.SetLEDColor(X, Y, Z1, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, Z2, Red, Green, Blue);
		}
		break;
	}
}
