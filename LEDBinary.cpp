// LEDBinary.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDBinary.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDBinary Binary;

LEDBinary::LEDBinary() {

}

int LEDBinary::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDBinary::StartBinary() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	StepCounter = 0;
	StepTarget = random(1000, 1500);
	AngleStepCounter = 0;
	AngleStepsPerCenterMove = random(5, 25);
	NumberOfCenters = 1;
	NextNumberOfCenters = 0;
	ChangeNumberOfCentersCounter = 0;
	ChangeNumberOfCentersTarget = random(50, 100);
	for (int object = 0; object < 16; object++) {
		for (int color = 0; color < 3; color++) {
			Colors[object][color] = Cube.RandomColor();
		}
	}
	for (int center = 0; center < 8; center++) {
		Angles[center] = random(0, 8);
	}
	Move.InitializeCubeMove(2);
}

void LEDBinary::StepBinary() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartBinary();
	}
	// Erase previous items
	Center0X = Move.GetCurrentCubeMoveX();
	Center0Y = Move.GetCurrentCubeMoveY();
	Center0Z = Move.GetCurrentCubeMoveZ();
	DrawCenters(false);
	// Increment all the angles
	for (int a = 0; a < 8; a++) {
		Angles[a] = Cube.NextIndex(Angles[a], 8);
	}
	// Is it time to move the center(s)?
	AngleStepCounter++;
	if (AngleStepCounter >= AngleStepsPerCenterMove) {
		AngleStepCounter = 0;
		if (Move.AtEndOfCurrentCubeMoveSegment()) {
			Move.SetupNextCubeMoveSegment();
			Move.StartCubeMoveSegment();
		} else {
			Move.AdvanceToNextCubeMovePosition();
		}
	}
	// Is it time to change the number of centers?
	ChangeNumberOfCentersCounter++;
	if (ChangeNumberOfCentersCounter >= ChangeNumberOfCentersTarget) {
		ChangeNumberOfCentersCounter = 0;
		NextNumberOfCenters = Cube.NextIndex(NextNumberOfCenters, 14);
		// Continuously cycle from 1 to 8 then back down to 2 and start over
		if (NextNumberOfCenters < 8) {
			NumberOfCenters = NextNumberOfCenters + 1;
		} else {
			NumberOfCenters = 15 - NextNumberOfCenters;
		}
	}
	// Draw the current items
	Center0X = Move.GetCurrentCubeMoveX();
	Center0Y = Move.GetCurrentCubeMoveY();
	Center0Z = Move.GetCurrentCubeMoveZ();
	DrawCenters(true);
}

void LEDBinary::DrawCenters(bool OffOn) {
	// Center0 is always active
	DrawCenter(0, Center0X, Center0Y, Center0Z, OffOn);
	if (NumberOfCenters > 1) {
		DrawCenter(1, 7 - Center0X, 7 - Center0Y, 7 - Center0Z, OffOn);
	}
	if (NumberOfCenters > 2) {
		DrawCenter(1, Center0X, 7 - Center0Y, 7 - Center0Z, OffOn);
	}
	if (NumberOfCenters > 3) {
		DrawCenter(1, 7 - Center0X, Center0Y, Center0Z, OffOn);
	}
	if (NumberOfCenters > 4) {
		DrawCenter(1, 7 - Center0X, Center0Y, 7 - Center0Z, OffOn);
	}
	if (NumberOfCenters > 5) {
		DrawCenter(1, Center0X, 7 - Center0Y, Center0Z, OffOn);
	}
	if (NumberOfCenters > 6) {
		DrawCenter(1, Center0X, Center0Y, 7 - Center0Z, OffOn);
	}
	if (NumberOfCenters > 7) {
		DrawCenter(1, 7 - Center0X, 7 - Center0Y, Center0Z, OffOn);
	}
}


void LEDBinary::DrawCenter(int CenterIndex, int X, int Y, int Z, bool OffOn) {
	int XOffset = GetXOffset(Angles[CenterIndex]);
	int YOffset = GetYOffset(Angles[CenterIndex]);
	int Object1Index = CenterIndex * 2;
	int Object2Index = CenterIndex * 2 + 1;
	DrawObject(Object1Index, X + XOffset, Y + YOffset, Z, OffOn);
	DrawObject(Object2Index, X - XOffset, Y - YOffset, Z, OffOn);
}

void LEDBinary::DrawObject(int ObjectIndex, int X, int Y, int Z, bool OffOn) {
	if (OffOn) {
		Cube.SetLEDColor(X, Y, Z, Colors[ObjectIndex][0], Colors[ObjectIndex][1], Colors[ObjectIndex][2]);
	} else {
		Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
	}
}

int LEDBinary::GetXOffset(int angle) {
	switch(angle) {
	case 0:
		return 1;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 0;
		break;
	case 3:
		return -1;
		break;
	case 4:
		return -1;
		break;
	case 5:
		return -1;
		break;
	case 6:
		return 0;
		break;
	case 7:
		return 1;
		break;
	}
}

int LEDBinary::GetYOffset(int angle) {
	switch(angle) {
	case 0:
		return 0;
		break;
	case 1:
		return 1;
		break;
	case 2:
		return 1;
		break;
	case 3:
		return 1;
		break;
	case 4:
		return 0;
		break;
	case 5:
		return -1;
		break;
	case 6:
		return -1;
		break;
	case 7:
		return -1;
		break;
	}
}
