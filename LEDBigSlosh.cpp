// LEDBigSlosh.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDBigSlosh.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDBigSlosh BigSlosh;

LEDBigSlosh::LEDBigSlosh() {

}

int LEDBigSlosh::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDBigSlosh::StartBigSlosh() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	StepCounter = 0;
	StepTarget = random(50, 100);
	CurrentAngle = 0;
	CurrentDirection = 0;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	Axis = random(0, 2);
	Width = random(1, 9);
	if (Width == 8) {
		Offset = 0;
	} else {
		Offset = random(0, (9 - Width));
	}
	// Draw the initial set of slabs
	for (int s = 0; s < 8; s++) {
		DrawSlab(s, Red, Green, Blue);
	}
}

void LEDBigSlosh::StepBigSlosh() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartBigSlosh();
	}
	// Take one slab off and put one slab on
	switch (CurrentAngle) {
	case 0:
		DrawSlab(0, 0, 0, 0);
		DrawSlab(8, Red, Green, Blue);
		break;
	case 1:
		DrawSlab(1, 0, 0, 0);
		DrawSlab(9, Red, Green, Blue);
		break;
	case 2:
		DrawSlab(2, 0, 0, 0);
		DrawSlab(10, Red, Green, Blue);
		break;
	case 3:
		DrawSlab(3, 0, 0, 0);
		DrawSlab(11, Red, Green, Blue);
		break;
	case 4:
		DrawSlab(4, 0, 0, 0);
		DrawSlab(12, Red, Green, Blue);
		break;
	case 5:
		DrawSlab(5, 0, 0, 0);
		DrawSlab(13, Red, Green, Blue);
		break;
	case 6:
		DrawSlab(6, 0, 0, 0);
		DrawSlab(14, Red, Green, Blue);
		break;
	case 7:
		DrawSlab(7, 0, 0, 0);
		DrawSlab(15, Red, Green, Blue);
		break;
	case 8:
		DrawSlab(8, 0, 0, 0);
		DrawSlab(16, Red, Green, Blue);
		break;
	case 9:
		DrawSlab(9, 0, 0, 0);
		DrawSlab(17, Red, Green, Blue);
		break;
	case 10:
		DrawSlab(17, 0, 0, 0);
		DrawSlab(9, Red, Green, Blue);
		break;
	case 11:
		DrawSlab(16, 0, 0, 0);
		DrawSlab(8, Red, Green, Blue);
		break;
	case 12:
		DrawSlab(15, 0, 0, 0);
		DrawSlab(7, Red, Green, Blue);
		break;
	case 13:
		DrawSlab(14, 0, 0, 0);
		DrawSlab(6, Red, Green, Blue);
		break;
	case 14:
		DrawSlab(13, 0, 0, 0);
		DrawSlab(5, Red, Green, Blue);
		break;
	case 15:
		DrawSlab(12, 0, 0, 0);
		DrawSlab(4, Red, Green, Blue);
		break;
	case 16:
		DrawSlab(11, 0, 0, 0);
		DrawSlab(3, Red, Green, Blue);
		break;
	case 17:
		DrawSlab(10, 0, 0, 0);
		DrawSlab(2, Red, Green, Blue);
		break;
	case 18:
		DrawSlab(9, 0, 0, 0);
		DrawSlab(1, Red, Green, Blue);
		break;
	case 19:
		DrawSlab(8, 0, 0, 0);
		DrawSlab(0, Red, Green, Blue);
		break;
	}
	CurrentAngle = Cube.NextIndex(CurrentAngle, 20);
}

void LEDBigSlosh::DrawSlab(int Position, int Red, int Green, int Blue) {
	int X;
	int Y;
	int Z;
	int XLeft;
	int XRight;
	int YFront;
	int YRear;
	int ZBottom;
	int ZTop;
	int Orientation;
	// For positions 0..4, "Z" is 7 - Position, "XLeft" is 0 and "XRight" is 2.
	// For positions 5..12 "X" is Position - 5, "ZBottom" is 0 and "ZTop" is 2.
	// For positions 13..17 "Z" is Position - 10, "XLeft" is 5 and "XRight" is 7.
	// "YFront" is Offset and "YRear" is "YFront" + Width - 1.
	// If Axis == 1, swap X and Y.
	YFront = Offset;
	YRear = YFront + Width - 1;
	switch (Position) {
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		Z = 7 - Position;
		XLeft = 0;
		XRight = 2;
		Orientation = 0;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		X = Position - 5;
		ZBottom = 0;
		ZTop = 2;
		Orientation = 1;
		break;
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		Z = Position - 10;
		XLeft = 5;
		XRight = 7;
		Orientation = 0;
		break;
	}
	// "Orientation" specifies a vertical (1) or horizontal (0) slab
	// "Axis" specifies sloshing around X-axis (1) or Y-axis (0)
	if (Orientation == 0) {
		// Horizontal slab
		for (X = XLeft; X <= XRight; X++) {
			for (Y = YFront; Y <= YRear; Y++) {
				if (Axis == 0) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				} else {
					Cube.SetLEDColor(Y, X, Z, Red, Green, Blue);
				}
			}
		}
	} else {
		// Vertical slab
		for (Y = YFront; Y <= YRear; Y++) {
			for (Z = ZBottom; Z <= ZTop; Z++) {
				if (Axis == 0) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				} else {
					Cube.SetLEDColor(Y, X, Z, Red, Green, Blue);
				}
			}
		}
	}
}

