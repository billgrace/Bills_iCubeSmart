// LEDRainbow.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDRainbow.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDRainbow Rainbow;

LEDRainbow::LEDRainbow() {

}

int LEDRainbow::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDRainbow::StartRainbow() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(10, 300));
	StepCounter = 0;
	StepTarget = random(200, 300);
	Stage = 10; // too high -> kicks in starting a new one
}

void LEDRainbow::StepRainbow() {
	int X;
	int Y;
	int Z;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartRainbow();
	}
	if (Stage >= 8) {
		// Time to start a new rainbow
		Cube.ClearImage();
		Stage = 0;
		// Direction = random(0, 14);
		Direction = random(0, 6);
	}
	// Direction and Stage are established - draw the next layer
	switch (Direction) {
	case 0:
		// Starting from +X face
		for (Y = 0; Y < 8; Y++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(Stage, Y, Z, Colors[Stage][0], Colors[Stage][1], Colors[Stage][2]);
			}
		}
		break;
	case 1:
		// Starting from -X face
		for (Y = 0; Y < 8; Y++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(7 - Stage, Y, Z, Colors[Stage][0], Colors[Stage][1], Colors[Stage][2]);
			}
		}
		break;
	case 2:
		// Starting from +Y face
		for (X = 0; X < 8; X++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(X, Stage, Z, Colors[Stage][0], Colors[Stage][1], Colors[Stage][2]);
			}
		}
		break;
	case 3:
		// Starting from -Y face
		for (X = 0; X < 8; X++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(X, 7 - Stage, Z, Colors[Stage][0], Colors[Stage][1], Colors[Stage][2]);
			}
		}
		break;
	case 4:
		// Starting from +Z face
		for (X = 0; X < 8; X++) {
			for (Y = 0; Y < 8; Y++) {
				Cube.SetLEDColor(X, Y, Stage, Colors[Stage][0], Colors[Stage][1], Colors[Stage][2]);
			}
		}
		break;
	case 5:
		// Starting from -Z face
		for (X = 0; X < 8; X++) {
			for (Y = 0; Y < 8; Y++) {
				Cube.SetLEDColor(X, Y, 7 - Stage, Colors[Stage][0], Colors[Stage][1], Colors[Stage][2]);
			}
		}
		break;
	case 6:
		// Starting from 0, 0, 0
		break;
	case 7:
		// Starting from 0, 0, 7
		break;
	case 8:
		// Starting from 0, 7, 0
		break;
	case 9:
		// Starting from 0, 7, 7
		break;
	case 10:
		// Starting from 7, 0, 0
		break;
	case 11:
		// Starting from 7, 0, 7
		break;
	case 12:
		// Starting from 7, 7, 0
		break;
	case 13:
		// Starting from 7, 7, 7
		break;
	}
	Stage++;
}
