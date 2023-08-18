// LEDPinWheel.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDPinWheel.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDPinWheel PinWheel;

LEDPinWheel::LEDPinWheel() {

}

int LEDPinWheel::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDPinWheel::StartPinWheel() {
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	StepCounter = 0;
	StepTarget = random(200, 500);
	StartNewCounter =0;
	StartNewTarget = random(50, 100);
	Normal = 0;
	StartANewPinWheel();
}

void LEDPinWheel::StepPinWheel() {
	int CounterAngle;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartPinWheel();
	}
	StartNewCounter++;
	if (StartNewCounter >= StartNewTarget) {
		StartNewCounter = 0;
		StartANewPinWheel();
	}
	// Mode 1 uses CounterAngle = 180 degrees from Angle
	CounterAngle = (Angle + 4) % 8;
	// Erase previous
	DrawArm(Angle, 0, 0, 0);
	if (Mode == 1) {
		DrawArm(CounterAngle, 0, 0, 0);
	}
	// Increment angle and, if necessary, offset
	Angle++;
	if (Angle >= 8) {
		Angle = 0;
		switch (OffsetDelta) {
		case -1:
			// We've been going down the axis
			if (CurrentOffset == 0) {
				// Time to turn around and head back up
				CurrentOffset = 1;
				OffsetDelta = 1;
			} else {
				// Just keep going down
				CurrentOffset--;
			}
			break;
		case 0:
			// The axial length is 8 so we're not moving along the axis
			// ... nothing to do here
			break;
		case 1:
			// We've been going up the axis
			if (CurrentOffset == MaxOffset) {
				// Time to turn around and head back down
				CurrentOffset--;
				OffsetDelta = -1;
			} else {
				// Just keep going up
				CurrentOffset++;
			}
			break;
		}
	}
	// With angle and offset updated, draw the new arm
	DrawArm(Angle, Red, Green, Blue);
	if (Mode == 1) {
		CounterAngle = (Angle + 4) % 8;
		DrawArm(CounterAngle, Red, Green, Blue);
	}
}


void LEDPinWheel::StartANewPinWheel() {
	Cube.ClearImage();
	// Now set up a new pinwheel
	Mode = random(0, 2);
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	Angle = 0;
	Normal = Cube.RandomButDifferent(Normal, 0, 6);
	Length = random(1, 9);
	// Length = Cube.GetGlobalInteger() + 1;
	MaxOffset = 8 - Length;
	CurrentOffset = 0;
	if (Length == 8) {
		OffsetDelta = 0;
	} else {
		OffsetDelta = 1;
	}
}

void LEDPinWheel::DrawArm(int ArmAngle, int Red, int Green, int Blue) {
	int X;
	int Y;
	int Z;
	int AStart;
	int AFinish;
	int Coordinate00;
	int Coordinate01;
	int Coordinate10;
	int Coordinate11;
	int Coordinate20;
	int Coordinate21;
	int Coordinate30;
	int Coordinate31;
	int Coordinate40;
	int Coordinate41;
	// Pick up all the coordinates for the given angle
	Coordinate00 = Move.GetPinWheelMovePosition0(ArmAngle, 0);
	Coordinate01 = Move.GetPinWheelMovePosition1(ArmAngle, 0);
	Coordinate10 = Move.GetPinWheelMovePosition0(ArmAngle, 1);
	Coordinate11 = Move.GetPinWheelMovePosition1(ArmAngle, 1);
	Coordinate20 = Move.GetPinWheelMovePosition0(ArmAngle, 2);
	Coordinate21 = Move.GetPinWheelMovePosition1(ArmAngle, 2);
	Coordinate30 = Move.GetPinWheelMovePosition0(ArmAngle, 3);
	Coordinate31 = Move.GetPinWheelMovePosition1(ArmAngle, 3);
	Coordinate40 = Move.GetPinWheelMovePosition0(ArmAngle, 4);
	Coordinate41 = Move.GetPinWheelMovePosition1(ArmAngle, 4);
	// Figure out the axis offset start and finish values
	AStart = CurrentOffset;
	AFinish = AStart + Length;
	// Draw the arm
	switch (Normal) {
	case 0:
		// +X
		for (X = AStart; X < AFinish; X++) {
			Cube.SetLEDColor(X, Coordinate00, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate10, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate20, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate30, Coordinate31, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate40, Coordinate41, Red, Green, Blue);
		}
		break;
	case 1:
		// -X
		for (X = 7 - AStart; X > (7 - AFinish); X--) {
			Cube.SetLEDColor(X, Coordinate00, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate10, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate20, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate30, Coordinate31, Red, Green, Blue);
			Cube.SetLEDColor(X, Coordinate40, Coordinate41, Red, Green, Blue);
		}
		break;
	case 2:
		// +Y
		for (Y = AStart; Y < AFinish; Y++) {
			Cube.SetLEDColor(Coordinate00, Y, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate10, Y, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate20, Y, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate30, Y, Coordinate31, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate40, Y, Coordinate41, Red, Green, Blue);
		}
		break;
	case 3:
		// -Y
		for (Y = 7 - AStart; Y > (7 - AFinish); Y--) {
			Cube.SetLEDColor(Coordinate00, Y, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate10, Y, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate20, Y, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate30, Y, Coordinate31, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate40, Y, Coordinate41, Red, Green, Blue);
		}
		break;
	case 4:
		// +Z
		for (Z = AStart; Z < AFinish; Z++) {
			Cube.SetLEDColor(Coordinate00, Z, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate10, Z, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate20, Z, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate30, Z, Coordinate31, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate40, Z, Coordinate41, Red, Green, Blue);
		}
		break;
	case 5:
		// -Z
		for (Z = 7 - AStart; Z > (7 - AFinish); Z--) {
			Cube.SetLEDColor(Coordinate00, Z, Coordinate01, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate10, Z, Coordinate11, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate20, Z, Coordinate21, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate30, Z, Coordinate31, Red, Green, Blue);
			Cube.SetLEDColor(Coordinate40, Z, Coordinate41, Red, Green, Blue);
		}
		break;
	}
}


