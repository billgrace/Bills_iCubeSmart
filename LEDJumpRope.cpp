// LEDJumpRope.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDJumpRope.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDJumpRope JumpRope;

LEDJumpRope::LEDJumpRope() {

}

int LEDJumpRope::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDJumpRope::StartJumpRope() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	StepCounter = 0;
	StepTarget = random(200, 500);
	RopeColorChangeCounter = 0;
	RopeColorChangeTarget = random(10, 20);
	KidColorChangeCounter = 0;
	KidColorChangeTarget = random(5, 10);
	Angle = random(0, 12);
	Direction = random(0, 2);
	RopeRed = Cube.RandomColor();
	RopeGreen = Cube.RandomColor();
	RopeBlue = Cube.RandomColor();
	KidRed = Cube.RandomColor();
	KidGreen = Cube.RandomColor();
	KidBlue = Cube.RandomColor();
}

void LEDJumpRope::StepJumpRope() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartJumpRope();
	}
	// Turn off previous rope
	DrawScene(0, 0, 0, 0, 0, 0);
	// Update colors?
	RopeColorChangeCounter++;
	if (RopeColorChangeCounter >= RopeColorChangeTarget) {
		RopeColorChangeCounter = 0;
		RopeRed = Cube.RandomColor();
		RopeGreen = Cube.RandomColor();
		RopeBlue = Cube.RandomColor();
	}
	KidColorChangeCounter++;
	if (KidColorChangeCounter >= KidColorChangeTarget) {
		KidColorChangeCounter = 0;
		KidRed = Cube.RandomColor();
		KidGreen = Cube.RandomColor();
		KidBlue = Cube.RandomColor();
	}
	switch (Direction) {
	case 0:
		Angle++;
		if (Angle >= 12) {
			Angle = 0;
		}
		break;
	case 1:
		Angle--;
		if (Angle < 0) {
			Angle = 11;
		}
		break;
	}
	DrawScene(RopeRed, RopeGreen, RopeBlue, KidRed, KidGreen, KidBlue);
}

void LEDJumpRope::DrawScene(int RRed, int RGreen, int RBlue, int KRed, int KGreen, int KBlue) {
	int X1;
	int Z1;
	int X2;
	int Z2;
	int X3;
	int Z3;
	int X4;
	int Z4;
	int KidZ;
	switch (Angle) {
	case 0:
		X1 = 4;
		Z1 = 4;
		X2 = 5;
		Z2 = 4;
		X3 = 6;
		Z3 = 4;
		X4 = 7;
		Z4 = 4;
		KidZ = 3;
		break;
	case 1:
		X1 = 4;
		Z1 = 4;
		X2 = 5;
		Z2 = 5;
		X3 = 6;
		Z3 = 6;
		X4 = 7;
		Z4 = 7;
		KidZ = 2;
		break;
	case 2:
		X1 = 4;
		Z1 = 4;
		X2 = 4;
		Z2 = 5;
		X3 = 4;
		Z3 = 6;
		X4 = 4;
		Z4 = 7;
		KidZ = 1;
		break;
	case 3:
		X1 = 3;
		Z1 = 4;
		X2 = 3;
		Z2 = 5;
		X3 = 3;
		Z3 = 6;
		X4 = 3;
		Z4 = 7;
		KidZ = 0;
		break;
	case 4:
		X1 = 3;
		Z1 = 4;
		X2 = 2;
		Z2 = 5;
		X3 = 1;
		Z3 = 6;
		X4 = 0;
		Z4 = 7;
		KidZ = 1;
		break;
	case 5:
		X1 = 3;
		Z1 = 4;
		X2 = 2;
		Z2 = 4;
		X3 = 1;
		Z3 = 4;
		X4 = 0;
		Z4 = 4;
		KidZ = 2;
		break;
	case 6:
		X1 = 3;
		Z1 = 3;
		X2 = 2;
		Z2 = 3;
		X3 = 1;
		Z3 = 3;
		X4 = 0;
		Z4 = 3;
		KidZ = 3;
		break;
	case 7:
		X1 = 3;
		Z1 = 3;
		X2 = 2;
		Z2 = 2;
		X3 = 1;
		Z3 = 1;
		X4 = 0;
		Z4 = 0;
		KidZ = 4;
		break;
	case 8:
		X1 = 3;
		Z1 = 3;
		X2 = 3;
		Z2 = 2;
		X3 = 3;
		Z3 = 1;
		X4 = 3;
		Z4 = 0;
		KidZ = 5;
		break;
	case 9:
		X1 = 4;
		Z1 = 3;
		X2 = 4;
		Z2 = 2;
		X3 = 4;
		Z3 = 1;
		X4 = 4;
		Z4 = 0;
		KidZ = 6;
		break;
	case 10:
		X1 = 4;
		Z1 = 3;
		X2 = 5;
		Z2 = 2;
		X3 = 6;
		Z3 = 1;
		X4 = 7;
		Z4 = 0;
		KidZ = 5;
		break;
	case 11:
		X1 = 4;
		Z1 = 3;
		X2 = 5;
		Z2 = 3;
		X3 = 6;
		Z3 = 3;
		X4 = 7;
		Z4 = 3;
		KidZ = 4;
		break;
	}
	ShowRope(1, X1, Z1, RRed, RGreen, RBlue);
	ShowRope(2, X2, Z2, RRed, RGreen, RBlue);
	ShowRope(3, X3, Z3, RRed, RGreen, RBlue);
	ShowRope(4, X4, Z4, RRed, RGreen, RBlue);
	DrawKid(KidZ, KRed, KGreen, KBlue);
}

void LEDJumpRope::ShowRope(int Radius, int X, int Z, int Red, int Green, int Blue) {
	switch (Radius) {
	case 1:
		Cube.SetLEDColor(X, 0, Z, Red, Green, Blue);
		Cube.SetLEDColor(X, 7, Z, Red, Green, Blue);
		break;
	case 2:
		Cube.SetLEDColor(X, 0, Z, Red, Green, Blue);
		Cube.SetLEDColor(X, 7, Z, Red, Green, Blue);
		break;
	case 3:
		Cube.SetLEDColor(X, 1, Z, Red, Green, Blue);
		Cube.SetLEDColor(X, 6, Z, Red, Green, Blue);
		break;
	case 4:
		for (int Y = 2; Y < 6; Y++) {
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		}
		break;
	}
}

void LEDJumpRope::DrawKid(int Z, int Red, int Green, int Blue) {
	for (int X = 3; X < 5; X++) {
		for (int Y = 3; Y < 5; Y++) {
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, Z + 1, Red, Green, Blue);
		}
	}
}

