// Face.cpp

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
	Cube.SetAnimationStepSpeedPeriodTo(random(250, 350));
	StepCounter = 0;
	StepTarget = random(50, 100);
	CurrentFace = 0;
	PickFaceOrientations();
	PickColors();
}

void LEDFace::StepFace() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartFace();
	}
	DrawFace(CurrentFace);
	CurrentFace++;
	if (CurrentFace > 6) {
		CurrentFace = 0;
		Cube.ClearImage();
		PickFaceOrientations();
		PickColors();
	}
}

void LEDFace::PickFaceOrientations() {
	int i;
	int j;
	int k;
	int l;
	// We want the set of numbers from 0 to 5
	// ... but OUT of order
	// ... but STILL the same set of 6 numbers - none missing none duplicated
	// Start with everything in ascending order
	for (i = 0; i < 6; i++) {
		FaceOrientation[i] = i;
	}
	// Now swap things a few times in a random way
	for (i = 0; i < random(5, 10); i++) {
		j = random(0, 6);
		k = Cube.RandomButDifferent(j, 0, 6);
		l = FaceOrientation[j];
		FaceOrientation[j] = FaceOrientation[k];
		FaceOrientation[k] = l;
	}
}

void LEDFace::PickColors() {
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
}

void LEDFace::DrawFace(int Index) {
	int X;
	int Y;
	int Z;
	switch (FaceOrientation[Index]) {
	case 0:
		// +X
		for (Y = 0; Y < 8; Y++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(7, Y, Z, Red, Green, Blue);
			}
		}
		break;
	case 1:
		// -X
		for (Y = 0; Y < 8; Y++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(0, Y, Z, Red, Green, Blue);
			}
		}
		break;
	case 2:
		// +Y
		for (X = 0; X < 8; X++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(X, 7, Z, Red, Green, Blue);
			}
		}
		break;
	case 3:
		// -Y
		for (X = 0; X < 8; X++) {
			for (Z = 0; Z < 8; Z++) {
				Cube.SetLEDColor(X, 0, Z, Red, Green, Blue);
			}
		}
		break;
	case 4:
		// +Z
		for (X = 0; X < 8; X++) {
			for (Y = 0; Y < 8; Y++) {
				Cube.SetLEDColor(X, Y, 7, Red, Green, Blue);
			}
		}
		break;
	case 5:
		// -Z
		for (X = 0; X < 8; X++) {
			for (Y = 0; Y < 8; Y++) {
				Cube.SetLEDColor(X, Y, 0, Red, Green, Blue);
			}
		}
		break;
	}
}
