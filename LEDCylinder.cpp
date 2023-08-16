// LEDCylinder.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCylinder.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCylinder Cylinder;

LEDCylinder::LEDCylinder() {

}

int LEDCylinder::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCylinder::StartCylinder() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	StepCounter = 0;
	StepTarget = random(200, 500);
	StartANewCylinder();
}

void LEDCylinder::StepCylinder() {
	int X;
	int Y;
	int Z;
	int Coordinate00;
	int Coordinate01;
	int Coordinate10;
	int Coordinate11;
	int Coordinate20;
	int Coordinate21;
	int Coordinate30;
	int Coordinate31;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartCylinder();
	}
	if (Angle >= 28) {
		StartANewCylinder();
	}
	Coordinate00 = Move.GetCylinderMovePosition0(Angle, 0);
	Coordinate01 = Move.GetCylinderMovePosition1(Angle, 0);
	Coordinate10 = Move.GetCylinderMovePosition0(Angle, 1);
	Coordinate11 = Move.GetCylinderMovePosition1(Angle, 1);
	Coordinate20 = Move.GetCylinderMovePosition0(Angle, 2);
	Coordinate21 = Move.GetCylinderMovePosition1(Angle, 2);
	Coordinate30 = Move.GetCylinderMovePosition0(Angle, 3);
	Coordinate31 = Move.GetCylinderMovePosition1(Angle, 3);
	switch (Normal) {
	case 0:
		// +X
		for (X = 0; X < 8; X++) {
			Cube.SetLEDColor(X, Coordinate00, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate10, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate20, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate30, Coordinate31, Red, Green, Blue);
		}
		break;
	case 1:
		// -X
		for (X = 0; X < 8; X++) {
			Cube.SetLEDColor(X, 7 - Coordinate00, 7 - Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(X, 7 - Coordinate10, 7 - Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(X, 7 - Coordinate20, 7 - Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(X, 7 - Coordinate30, 7 - Coordinate31, Red, Green, Blue);
		}
		break;
	case 2:
		// +Y
		for (Y = 0; Y < 8; Y++) {
			Cube.SetLEDColor(Coordinate00, Y, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate10, Y, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate20, Y, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate30, Y, Coordinate31, Red, Green, Blue);
		}
		break;
	case 3:
		// -Y
		for (Y = 0; Y < 8; Y++) {
			Cube.SetLEDColor(7 - Coordinate00, Y, 7 - Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(7 - Coordinate10, Y, 7 - Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(7 - Coordinate20, Y, 7 - Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(7 - Coordinate30, Y, 7 - Coordinate31, Red, Green, Blue);
		}
		break;
	case 4:
		// +Z
		for (Z = 0; Z < 8; Z++) {
			Cube.SetLEDColor(Coordinate00, Coordinate01, Z, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate10, Coordinate11, Z, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate20, Coordinate21, Z, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate30, Coordinate31, Z, Red, Green, Blue);
		}
		break;
	case 5:
		// -Z
		for (Z = 0; Z < 8; Z++) {
			Cube.SetLEDColor(7 - Coordinate00, 7 - Coordinate01, Z, Red, Green, Blue);
			Cube.SetLEDColor(7 - Coordinate10, 7 - Coordinate11, Z, Red, Green, Blue);
			Cube.SetLEDColor(7 - Coordinate20, 7 - Coordinate21, Z, Red, Green, Blue);
			Cube.SetLEDColor(7 - Coordinate30, 7 - Coordinate31, Z, Red, Green, Blue);
		}
		break;
	}
	Angle++;
}

void LEDCylinder::StartANewCylinder() {
	// Normal: 0 => +X, 1 => -X, 2 => +Y, etc.
	Normal = Cube.RandomButDifferent(Normal, 0, 6);
	Angle = 0;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
}
