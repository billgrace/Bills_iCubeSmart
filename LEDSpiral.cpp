// LEDSpiral.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDSpiral.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDSpiral Spiral;

LEDSpiral::LEDSpiral() {

}

int LEDSpiral::SuggestedNumberOfAnimationCycles() {
	return random(3, 6);
}

void LEDSpiral::StartSpiral() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	AxisDirection = random(0, 6);
	AxisPosition1 = random(0, 6);
	AxisPosition2 = random(AxisPosition1, 6);
	CurrentPosition = 0;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	VaryTheColor = random(0, 2);
	Move.SetSpiralMovePattern(random(0, NumberOfSpiralPatterns));

}

void LEDSpiral::StepSpiral() {
	int X;
	int Y;
	int Z;
	if (VaryTheColor == 1) {
		int NewColor = Cube.VeryCloseColor(Red, Green, Blue);
		Red = Cube.RedPartOf(NewColor);
		Green = Cube.GreenPartOf(NewColor);
		Blue = Cube.BluePartOf(NewColor);
	}
	for (int AxisPosition = AxisPosition1; AxisPosition <= AxisPosition2; AxisPosition++) {
		switch(AxisDirection) {
		case 0:
			X = AxisPosition;
			Y = Move.GetSpiralMovePosition0(CurrentPosition);
			Z = Move.GetSpiralMovePosition1(CurrentPosition);
			break;
		case 1:
			X = Move.GetSpiralMovePosition1(CurrentPosition);
			Y = AxisPosition;
			Z = Move.GetSpiralMovePosition0(CurrentPosition);
			break;
		case 2:
			X = Move.GetSpiralMovePosition0(CurrentPosition);
			Y = Move.GetSpiralMovePosition1(CurrentPosition);
			Z = AxisPosition;
			break;
		case 3:
			X = AxisPosition;
			Y = Move.GetSpiralMovePosition1(CurrentPosition);
			Z = Move.GetSpiralMovePosition0(CurrentPosition);
			break;
		case 4:
			X = Move.GetSpiralMovePosition0(CurrentPosition);
			Y = AxisPosition;
			Z = Move.GetSpiralMovePosition1(CurrentPosition);
			break;
		case 5:
			X = Move.GetSpiralMovePosition1(CurrentPosition);
			Y = Move.GetSpiralMovePosition0(CurrentPosition);
			Z = AxisPosition;
			break;
		}
		Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
	}
	CurrentPosition++;
	if (CurrentPosition > 64) {
		StartSpiral();
	}
}
