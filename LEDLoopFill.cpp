// LEDLoopFill.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDLoopFill.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDLoopFill LoopFill;

LEDLoopFill::LEDLoopFill () {

}

int LEDLoopFill::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDLoopFill::StartLoopFill() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(20, 50));
	FaceCounter = 0;
	FaceTarget = random(3, 7);
	StartAFace();
}

void LEDLoopFill::StepLoopFill() {
	switch (Face) {
	case 0:
		// Starting face is +X
		X = 7 - Coordinate[Step][0];
		switch (Orientation) {
		case 0:
			// Up
			Y = Offset2;
			Z = Coordinate[Step][1] + Offset1;
			break;
		case 1:
			// Right
			Y = Coordinate[Step][1] + Offset1;
			Z = Offset2;
			break;
		case 2:
			// Down
			Y = Offset2;
			Z = 7 - Coordinate[Step][1] - Offset1;
			break;
		case 3:
			// Left
			Y = 7 - Coordinate[Step][1] - Offset1;
			Z = Offset2;
			break;
		}
		break;
	case 1:
		// Starting face is -X
		X = Coordinate[Step][0];
		switch (Orientation) {
		case 0:
			// Up
			Y = Offset2;
			Z = Coordinate[Step][1] + Offset1;
			break;
		case 1:
			// Right
			Y = Coordinate[Step][1] + Offset1;
			Z = Offset2;
			break;
		case 2:
			// Down
			Y = Offset2;
			Z = 7 - Coordinate[Step][1] - Offset1;
			break;
		case 3:
			// Left
			Y = 7 - Coordinate[Step][1] - Offset1;
			Z = Offset2;
			break;
		}
		break;
	case 2:
		// Starting face is +Y
		Y = 7 - Coordinate[Step][0];
		switch (Orientation) {
		case 0:
			// Up
			X = Offset2;
			Z = Coordinate[Step][1] + Offset1;
			break;
		case 1:
			// Right
			X = Coordinate[Step][1] + Offset1;
			Z = Offset2;
			break;
		case 2:
			// Down
			X = Offset2;
			Z = 7 - Coordinate[Step][1] - Offset1;
			break;
		case 3:
			// Left
			X = 7 - Coordinate[Step][1] - Offset1;
			Z = Offset2;
			break;
		}
		break;
	case 3:
		// Starting face is -Y
		Y = Coordinate[Step][0];
		switch (Orientation) {
		case 0:
			// Up
			X = Offset2;
			Z = Coordinate[Step][1] + Offset1;
			break;
		case 1:
			// Right
			X = Coordinate[Step][1] + Offset1;
			Z = Offset2;
			break;
		case 2:
			// Down
			X = Offset2;
			Z = 7 - Coordinate[Step][1] - Offset1;
			break;
		case 3:
			// Left
			X = 7 - Coordinate[Step][1] - Offset1;
			Z = Offset2;
			break;
		}
		break;
	case 4:
		// Starting face is +Z
		Z = 7 - Coordinate[Step][0];
		switch (Orientation) {
		case 0:
			X = Offset2;
			Y = Coordinate[Step][1] + Offset1;
			// Up
			break;
		case 1:
			// Right
			X = Coordinate[Step][1] + Offset1;
			Y = Offset2;
			break;
		case 2:
			// Down
			X = Offset2;
			Y = 7 - Coordinate[Step][1] - Offset1;
			break;
		case 3:
			// Left
			X = 7 - Coordinate[Step][1] - Offset1;
			Y = Offset2;
			break;
		}
		break;
	case 5:
		// Starting face is -Z
		Z = Coordinate[Step][0];
		switch (Orientation) {
		case 0:
			// Up
			X = Offset2;
			Y = Coordinate[Step][1] + Offset1;
			break;
		case 1:
			// Right
			X = Coordinate[Step][1] + Offset1;
			Y = Offset2;
			break;
		case 2:
			// Down
			X = Offset2;
			Y = 7 - Coordinate[Step][1] - Offset1;
			break;
		case 3:
			// Left
			X = 7 - Coordinate[Step][1] - Offset1;
			Y = Offset2;
			break;
		}
		break;
	}
	Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
	Step++;
	if (Step >= 12) {
		StartALoop();
	}
}

void LEDLoopFill::StartALoop() {
	LoopCounter++;
	if (LoopCounter >= LoopTarget) {
		StartAFace();
	}
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	Step = 0;

	Orientation = random(0, 4);

	Offset1 = random(0, 3);
	Offset2 = random(0, 8);
}

void LEDLoopFill::StartAFace() {
	FaceCounter++;
	if (FaceCounter >= FaceTarget) {
		StartLoopFill();
	}
	LoopCounter = 0;
	LoopTarget = random(10, 30);
	Cube.ClearImage();
	LoopCounter = 0;
	Face = random(0, 6);
	StartALoop();
}
