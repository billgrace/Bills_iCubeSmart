// LEDIter.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDIter.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDIter Iter;

LEDIter::LEDIter() {
}

int LEDIter::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDIter::StartIter() {
	int FuelCompositeColor;
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(20, 40));
	CurrentFuelSpeed = random(50, 100);
	TargetFuelSpeed = random(5, 20);
	FrameRed = Cube.RandomColor();
	FrameGreen = Cube.RandomColor();
	FrameBlue = Cube.RandomColor();
	FuelCompositeColor = Cube.VeryDifferentColor(FrameRed, FrameGreen, FrameBlue);
	FuelRed = Cube.RedPartOf(FuelCompositeColor);
	FuelGreen = Cube.GreenPartOf(FuelCompositeColor);
	FuelBlue = Cube.BluePartOf(FuelCompositeColor);
	StepCounter = 0;
	StepTarget = random(200, 500);
	StageNumber = 0;
	LEDNumber = 0;
}

void LEDIter::StepIter() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartIter();
	}
	switch(StageNumber) {
	case 0:
		// Frame center cube
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(3, 3, 3, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(3, 3, 4, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(3, 4, 3, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(3, 4, 4, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(4, 3, 3, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(4, 3, 4, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(4, 4, 3, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 7:
			Cube.SetLEDColor(4, 4, 4, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 1;
			break;
		}
		break;
	case 1:
		// Frame lower front
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(0, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(1, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(2, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(3, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(4, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(5, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(6, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 7:
			Cube.SetLEDColor(7, 0, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 2;
			break;
		}
		break;
	case 2:
		// Frame lower right
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(7, 1, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(7, 2, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(7, 3, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(7, 4, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(7, 5, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(7, 6, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(7, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 3;
			break;
		}
		break;
	case 3:
		// Frame lower rear
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(6, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(5, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(4, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(3, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(2, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(1, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(0, 7, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 4;
			break;
		}
		break;
	case 4:
		// Frame lower left
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(0, 6, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(0, 5, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(0, 4, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(0, 3, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(0, 2, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(0, 1, 0, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 5;
			break;
		}
		break;
	case 5:
		// Frame upper front
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(0, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(1, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(2, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(3, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(4, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(5, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(6, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 7:
			Cube.SetLEDColor(7, 0, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 6;
			break;
		}
		break;
	case 6:
		// Frame upper right
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(7, 1, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(7, 2, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(7, 3, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(7, 4, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(7, 5, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(7, 6, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(7, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 7;
			break;
		}
		break;
	case 7:
		// Frame upper rear
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(6, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(5, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(4, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(3, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(2, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(1, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 6:
			Cube.SetLEDColor(0, 7, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 8;
			break;
		}
		break;
	case 8:
		// Frame upper left
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(0, 6, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(0, 5, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 2:
			Cube.SetLEDColor(0, 4, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 3:
			Cube.SetLEDColor(0, 3, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 4:
			Cube.SetLEDColor(0, 2, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 5:
			Cube.SetLEDColor(0, 1, 7, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 9;
			break;
		}
		break;
	case 9:
		// Front lower left diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(1, 1, 1, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(2, 2, 2, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 10;
			break;
		}
		break;
	case 10:
		// Front lower right diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(6, 1, 1, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(5, 2, 2, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 11;
			break;
		}
		break;
	case 11:
		// Front upper left diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(1, 1, 6, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(2, 2, 5, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 12;
			break;
		}
		break;
	case 12:
		// Front upper right diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(6, 1, 6, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(5, 2, 5, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 13;
			break;
		}
		break;
	case 13:
		// Rear lower left diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(1, 6, 1, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(2, 5, 2, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 14;
			break;
		}
		break;
	case 14:
		// Rear lower right diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(6, 6, 1, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(5, 5, 2, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 15;
			break;
		}
		break;
	case 15:
		// Rear upper left diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(1, 6, 6, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(2, 5, 5, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 16;
			break;
		}
		break;
	case 16:
		// Rear upper right diagonal
		switch(LEDNumber) {
		case 0:
			Cube.SetLEDColor(6, 6, 6, FrameRed, FrameGreen, FrameBlue);
			LEDNumber++;
			break;
		case 1:
			Cube.SetLEDColor(5, 5, 5, FrameRed, FrameGreen, FrameBlue);
			LEDNumber = 0;
			StageNumber = 17;
			Cube.SetAnimationStepSpeedPeriodTo(CurrentFuelSpeed);
			break;
		}
		break;
	case 17:
		// Fuel put in place in position0
		switch(LEDNumber) {
		case 0:
			DrawFuelCube(1, 1, 3, true);
			LEDNumber++;
			break;
		case 1:
			DrawFuelCube(5, 1, 3, true);
			LEDNumber++;
			break;
		case 2:
			DrawFuelCube(5, 5, 3, true);
			LEDNumber++;
			break;
		case 3:
			DrawFuelCube(1, 5, 3, true);
			LEDNumber = 0;
			StageNumber = 18;
			break;
		}
		break;
	case 18:
		// Fuel rotate to position1
		DrawFuelCube(1, 1, 3, false);
		DrawFuelCube(5, 1, 3, false);
		DrawFuelCube(5, 5, 3, false);
		DrawFuelCube(1, 5, 3, false);
		DrawFuelCube(2, 1, 3, true);
		DrawFuelCube(5, 2, 3, true);
		DrawFuelCube(4, 5, 3, true);
		DrawFuelCube(1, 4, 3, true);
		StageNumber = 19;
		break;
	case 19:
		// Fuel rotate to position2
		DrawFuelCube(2, 1, 3, false);
		DrawFuelCube(5, 2, 3, false);
		DrawFuelCube(4, 5, 3, false);
		DrawFuelCube(1, 4, 3, false);
		DrawFuelCube(3, 1, 3, true);
		DrawFuelCube(5, 3, 3, true);
		DrawFuelCube(3, 5, 3, true);
		DrawFuelCube(1, 3, 3, true);
		StageNumber = 20;
		break;
	case 20:
		// Fuel rotate to position3
		DrawFuelCube(3, 1, 3, false);
		DrawFuelCube(5, 3, 3, false);
		DrawFuelCube(3, 5, 3, false);
		DrawFuelCube(1, 3, 3, false);
		DrawFuelCube(4, 1, 3, true);
		DrawFuelCube(5, 4, 3, true);
		DrawFuelCube(2, 5, 3, true);
		DrawFuelCube(1, 2, 3, true);
		StageNumber = 21;
		break;
	case 21:
		// Fuel rotate back to position0
		DrawFuelCube(4, 1, 3, false);
		DrawFuelCube(5, 4, 3, false);
		DrawFuelCube(2, 5, 3, false);
		DrawFuelCube(1, 2, 3, false);
		DrawFuelCube(1, 1, 3, true);
		DrawFuelCube(5, 1, 3, true);
		DrawFuelCube(5, 5, 3, true);
		DrawFuelCube(1, 5, 3, true);
		StageNumber = 18;
		if (CurrentFuelSpeed > TargetFuelSpeed) {
			CurrentFuelSpeed--;
			Cube.SetAnimationStepSpeedPeriodTo(CurrentFuelSpeed);
		}
		break;
	}
}

void LEDIter::DrawFuelCube(int X, int Y, int Z, bool OffOn) {
	// Parameters locate front lower left corner of fuel cube
	int Red;
	int Green;
	int Blue;
	if (OffOn) {
		Red = FuelRed;
		Green = FuelGreen;
		Blue = FuelBlue;
	} else {
		Red = 0;
		Green = 0;
		Blue = 0;
	}
	Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y, Z + 1, Red, Green, Blue);
	Cube.SetLEDColor(X, Y + 1, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y + 1, Z + 1, Red, Green, Blue);
	Cube.SetLEDColor(X + 1, Y, Z, Red, Green, Blue);
	Cube.SetLEDColor(X + 1, Y, Z + 1, Red, Green, Blue);
	Cube.SetLEDColor(X + 1, Y + 1, Z, Red, Green, Blue);
	Cube.SetLEDColor(X + 1, Y + 1, Z + 1, Red, Green, Blue);

}