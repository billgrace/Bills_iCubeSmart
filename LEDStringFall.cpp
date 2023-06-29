// LEDStringFall.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDStringFall.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDStringFall StringFall;

LEDStringFall::LEDStringFall() {

}

int LEDStringFall::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDStringFall::StartStringFall() {
	TopLevel = random(4, 8);
	BottomLevel = random(0, TopLevel);
	// Initialize local color storage
	for (int X = 0; X < 8; X++) {
		for (int Y = 0; Y < 8; Y++) {
			ElementColor[X][Y][0] = TopLevel;
			ElementColor[X][Y][1] = Cube.RandomColor();
			ElementColor[X][Y][2] = Cube.RandomColor();
			ElementColor[X][Y][3] = Cube.RandomColor();
		}
	}
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	Move.SetSpiralMovePattern(random(0, NumberOfSpiralPatterns));
	CurrentStage = 0;
	CurrentPosition = 0;
}

void LEDStringFall::StepStringFall() {
	CurrentX = Move.GetSpiralMovePosition0(CurrentPosition);
	CurrentY = Move.GetSpiralMovePosition1(CurrentPosition);
	CurrentZ = ElementColor[CurrentX][CurrentY][0];
	CurrentRed = ElementColor[CurrentX][CurrentY][1];
	CurrentGreen = ElementColor[CurrentX][CurrentY][2];
	CurrentBlue = ElementColor[CurrentX][CurrentY][3];
	switch (CurrentStage) {
	case 0:
		Cube.SetLEDColor(CurrentX, CurrentY, CurrentZ, CurrentRed, CurrentGreen, CurrentBlue);
		CurrentPosition++;
		if (CurrentPosition >= 64) {
			CurrentPosition = 0;
			CurrentStage = 1;
		}
		break;
	case 1:
		if (CurrentZ > BottomLevel) {
			Cube.SetLEDColor(CurrentX, CurrentY, CurrentZ, 0, 0, 0);
			CurrentZ--;
			ElementColor[CurrentX][CurrentY][0] = CurrentZ;
			Cube.SetLEDColor(CurrentX, CurrentY, CurrentZ, CurrentRed, CurrentGreen, CurrentBlue);
		} else {
			CurrentPosition++;
			if (CurrentPosition >= 64) {
				CurrentPosition = 63;
				CurrentStage = 2;
			}
		}
		break;
	case 2:
		Cube.SetLEDColor(CurrentX, CurrentY, CurrentZ, 0, 0, 0);
		CurrentPosition--;
		if (CurrentPosition < 0) {
			StartStringFall();
		}
		break;
	}
}
