// LEDMovingAxes.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDMovingAxes.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDMovingAxes MovingAxes;

LEDMovingAxes::LEDMovingAxes() {
}

int LEDMovingAxes::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDMovingAxes::StartMovingAxes() {
	Mode[0] = random(0, 2);
	Mode[1] = random(0, 2);
	Mode[2] = random(0, 2);
	NumberOfAxisSets = random(1, 4);
	AxisColorChangeInterval = random(2, 5);
	StepCount = 0;
	MaxStepCount = random(100, 250);
	X1AxisRed = Cube.RandomColor();
	X1AxisGreen = Cube.RandomColor();
	X1AxisBlue = Cube.RandomColor();
	Y1AxisRed = Cube.RandomColor();
	Y1AxisGreen = Cube.RandomColor();
	Y1AxisBlue = Cube.RandomColor();
	Z1AxisRed = Cube.RandomColor();
	Z1AxisGreen = Cube.RandomColor();
	Z1AxisBlue = Cube.RandomColor();
	X1AxisPosition = random(0, 8);
	Y1AxisPosition = random(0, 8);
	Z1AxisPosition = random(0, 8);
	CurrentMotionAxis1 = random(0, 3);
	CurrentMotionDirection1 = Cube.RandomPickOfTwo(-1, 1);
	MotionModeAxis1 = random(0, 2);
	MotionDirectionChangeInterval1 = SetMotionDirectionChangeInterval(MotionModeAxis1);
	MotionModeAngle1 = 0;
	X2AxisRed = Cube.RandomColor();
	X2AxisGreen = Cube.RandomColor();
	X2AxisBlue = Cube.RandomColor();
	Y2AxisRed = Cube.RandomColor();
	Y2AxisGreen = Cube.RandomColor();
	Y2AxisBlue = Cube.RandomColor();
	Z2AxisRed = Cube.RandomColor();
	Z2AxisGreen = Cube.RandomColor();
	Z2AxisBlue = Cube.RandomColor();
	X2AxisPosition = random(0, 8);
	Y2AxisPosition = random(0, 8);
	Z2AxisPosition = random(0, 8);
	CurrentMotionAxis2 = random(0, 3);
	CurrentMotionDirection2 = Cube.RandomPickOfTwo(-1, 1);
	MotionModeAxis2 = random(0, 2);
	MotionDirectionChangeInterval2 = SetMotionDirectionChangeInterval(MotionModeAxis2);
	MotionModeAngle2 = 0;
	X3AxisRed = Cube.RandomColor();
	X3AxisGreen = Cube.RandomColor();
	X3AxisBlue = Cube.RandomColor();
	Y3AxisRed = Cube.RandomColor();
	Y3AxisGreen = Cube.RandomColor();
	Y3AxisBlue = Cube.RandomColor();
	Z3AxisRed = Cube.RandomColor();
	Z3AxisGreen = Cube.RandomColor();
	Z3AxisBlue = Cube.RandomColor();
	X3AxisPosition = random(0, 8);
	Y3AxisPosition = random(0, 8);
	Z3AxisPosition = random(0, 8);
	CurrentMotionAxis3 = random(0, 3);
	CurrentMotionDirection3 = Cube.RandomPickOfTwo(-1, 1);
	MotionModeAxis3 = random(0, 2);
	MotionDirectionChangeInterval3 = SetMotionDirectionChangeInterval(MotionModeAxis3);
	MotionModeAngle3 = 0;
	Cube.SetAnimationStepSpeedPeriodTo(random(100, 200));
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
}

int LEDMovingAxes::SetMotionDirectionChangeInterval(int MotionMode) {
	int ReturnValue;
	switch (MotionMode) {
	case 0:
		ReturnValue = random(3, 5);
		break;
	case 1:
		ReturnValue = random(13, 25);
		break;
	}
	return ReturnValue;
}

// Something to show

void LEDMovingAxes::StepMovingAxes() {
	int NewAxisCompositeColor;
	// Check to see if we're done now
	StepCount++;
	if (StepCount > MaxStepCount) {
		StartMovingAxes();
	}
	// Erase previous view
	DrawAxes(true);
	// Now and then vary one of the axis colors
	if ((StepCount % AxisColorChangeInterval) == 0){
		switch(random(0, 9)) {
		case 0:
			NewAxisCompositeColor = Cube.VeryCloseColor(X1AxisRed, X1AxisGreen, X1AxisBlue);
			X1AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			X1AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			X1AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 1:
			NewAxisCompositeColor = Cube.VeryCloseColor(Y1AxisRed, Y1AxisGreen, Y1AxisBlue);
			Y1AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			Y1AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			Y1AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 2:
			NewAxisCompositeColor = Cube.VeryCloseColor(Z1AxisRed, Z1AxisGreen, Z1AxisBlue);
			Z1AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			Z1AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			Z1AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 3:
			NewAxisCompositeColor = Cube.VeryCloseColor(X2AxisRed, X2AxisGreen, X2AxisBlue);
			X2AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			X2AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			X2AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 4:
			NewAxisCompositeColor = Cube.VeryCloseColor(Y2AxisRed, Y2AxisGreen, Y2AxisBlue);
			Y2AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			Y2AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			Y2AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 5:
			NewAxisCompositeColor = Cube.VeryCloseColor(Z2AxisRed, Z2AxisGreen, Z2AxisBlue);
			Z2AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			Z2AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			Z2AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 6:
			NewAxisCompositeColor = Cube.VeryCloseColor(X3AxisRed, X3AxisGreen, X3AxisBlue);
			X3AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			X3AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			X3AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 7:
			NewAxisCompositeColor = Cube.VeryCloseColor(Y3AxisRed, Y3AxisGreen, Y3AxisBlue);
			Y3AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			Y3AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			Y3AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		case 8:
			NewAxisCompositeColor = Cube.VeryCloseColor(Z3AxisRed, Z3AxisGreen, Z3AxisBlue);
			Z3AxisRed = Cube.RedPartOf(NewAxisCompositeColor);
			Z3AxisGreen = Cube.GreenPartOf(NewAxisCompositeColor);
			Z3AxisBlue = Cube.BluePartOf(NewAxisCompositeColor);
			break;
		}
	}
	// Now and then vary the direction of motion
	if ((StepCount % MotionDirectionChangeInterval1) == 0) {
		switch(CurrentMotionAxis1) {
		case 0:
			CurrentMotionAxis1 = Cube.RandomPickOfTwo(1, 2);
			break;
		case 1:
			CurrentMotionAxis1 = Cube.RandomPickOfTwo(0, 2);
			break;
		case 2:
			CurrentMotionAxis1 = Cube.RandomPickOfTwo(0, 1);
			break;
		}
	}
	if ((StepCount % MotionDirectionChangeInterval2) == 0) {
		switch(CurrentMotionAxis2) {
		case 0:
			CurrentMotionAxis2 = Cube.RandomPickOfTwo(1, 2);
			break;
		case 1:
			CurrentMotionAxis2 = Cube.RandomPickOfTwo(0, 2);
			break;
		case 2:
			CurrentMotionAxis2 = Cube.RandomPickOfTwo(0, 1);
			break;
		}
	}
	if ((StepCount % MotionDirectionChangeInterval3) == 0) {
		switch(CurrentMotionAxis3) {
		case 0:
			CurrentMotionAxis3 = Cube.RandomPickOfTwo(1, 2);
			break;
		case 1:
			CurrentMotionAxis3 = Cube.RandomPickOfTwo(0, 2);
			break;
		case 2:
			CurrentMotionAxis3 = Cube.RandomPickOfTwo(0, 1);
			break;
		}
	}
	// Move
	switch (MotionModeAxis1) {
	case 0:
		// Linear motion
		switch (CurrentMotionAxis1) {
		case 0:
			X1AxisPosition = NextPosition1(X1AxisPosition);
			break;
		case 1:
			Y1AxisPosition = NextPosition1(Y1AxisPosition);
			break;
		case 2:
			Z1AxisPosition = NextPosition1(Z1AxisPosition);
			break;
		}
		break;
	case 1:
		// Circular motion
		switch (CurrentMotionAxis1) {
		case 0:
			Y1AxisPosition = Move.GetCircleMoveX(MotionModeAngle1);
			Z1AxisPosition = Move.GetCircleMoveY(MotionModeAngle1);
			break;
		case 1:
			X1AxisPosition = Move.GetCircleMoveX(MotionModeAngle1);
			Z1AxisPosition = Move.GetCircleMoveY(MotionModeAngle1);
			break;
		case 2:
			X1AxisPosition = Move.GetCircleMoveX(MotionModeAngle1);
			Y1AxisPosition = Move.GetCircleMoveY(MotionModeAngle1);
			break;
		}
		MotionModeAngle1 = Cube.NextIndex(MotionModeAngle1, 12);
		break;
	}
	switch (MotionModeAxis2) {
	case 0:
		// Linear motion
		switch (CurrentMotionAxis2) {
		case 0:
			X2AxisPosition = NextPosition2(X2AxisPosition);
			break;
		case 1:
			Y2AxisPosition = NextPosition2(Y2AxisPosition);
			break;
		case 2:
			Z2AxisPosition = NextPosition2(Z2AxisPosition);
			break;
		}
		break;
	case 1:
		// Circular motion
		switch (CurrentMotionAxis1) {
		case 0:
			Y2AxisPosition = Move.GetCircleMoveX(MotionModeAngle2);
			Z2AxisPosition = Move.GetCircleMoveY(MotionModeAngle2);
			break;
		case 1:
			X2AxisPosition = Move.GetCircleMoveX(MotionModeAngle2);
			Z2AxisPosition = Move.GetCircleMoveY(MotionModeAngle2);
			break;
		case 2:
			X2AxisPosition = Move.GetCircleMoveX(MotionModeAngle2);
			Y2AxisPosition = Move.GetCircleMoveY(MotionModeAngle2);
			break;
		}
		MotionModeAngle2 = Cube.NextIndex(MotionModeAngle2, 12);
		break;
	}
	switch (MotionModeAxis3) {
	case 0:
		// Linear motion
		switch (CurrentMotionAxis3) {
		case 0:
			X3AxisPosition = NextPosition3(X3AxisPosition);
			break;
		case 1:
			Y3AxisPosition = NextPosition3(Y3AxisPosition);
			break;
		case 2:
			Z3AxisPosition = NextPosition3(Z3AxisPosition);
			break;
		}
		break;
	case 1:
		// Circular motion
		switch (CurrentMotionAxis1) {
		case 0:
			Y3AxisPosition = Move.GetCircleMoveX(MotionModeAngle3);
			Z3AxisPosition = Move.GetCircleMoveY(MotionModeAngle3);
			break;
		case 1:
			X3AxisPosition = Move.GetCircleMoveX(MotionModeAngle3);
			Z3AxisPosition = Move.GetCircleMoveY(MotionModeAngle3);
			break;
		case 2:
			X3AxisPosition = Move.GetCircleMoveX(MotionModeAngle3);
			Y3AxisPosition = Move.GetCircleMoveY(MotionModeAngle3);
			break;
		}
		MotionModeAngle3 = Cube.NextIndex(MotionModeAngle3, 12);
		break;
	}
	// Show new view
	DrawAxes(false);
}

int LEDMovingAxes::NextPosition1(int CurrentPosition) {
	int NewPosition = CurrentPosition + CurrentMotionDirection1;
	if (NewPosition < 0) {
		CurrentMotionDirection1 = 1;
		NewPosition = 1;
	}
	if (NewPosition > 7) {
		CurrentMotionDirection1 = -1;
		NewPosition = 6;
	}
	return NewPosition;
}

int LEDMovingAxes::NextPosition2(int CurrentPosition) {
	int NewPosition = CurrentPosition + CurrentMotionDirection2;
	if (NewPosition < 0) {
		CurrentMotionDirection2 = 1;
		NewPosition = 1;
	}
	if (NewPosition > 7) {
		CurrentMotionDirection2 = -1;
		NewPosition = 6;
	}
	return NewPosition;
}

int LEDMovingAxes::NextPosition3(int CurrentPosition) {
	int NewPosition = CurrentPosition + CurrentMotionDirection3;
	if (NewPosition < 0) {
		CurrentMotionDirection3 = 1;
		NewPosition = 1;
	}
	if (NewPosition > 7) {
		CurrentMotionDirection3 = -1;
		NewPosition = 6;
	}
	return NewPosition;
}

void LEDMovingAxes::DrawAxes(bool Erase) {
	// Make the origin colors a combination of their three axis colors
	int Origin1Red = Cube.SumOfThreeColors(X1AxisRed, Y1AxisRed, Z1AxisRed);
	int Origin1Green = Cube.SumOfThreeColors(X1AxisGreen, Y1AxisGreen, Z1AxisGreen);
	int Origin1Blue = Cube.SumOfThreeColors(X1AxisBlue, Y1AxisBlue, Z1AxisBlue);
	int Origin2Red = Cube.SumOfThreeColors(X2AxisRed, Y2AxisRed, Z2AxisRed);
	int Origin2Green = Cube.SumOfThreeColors(X2AxisGreen, Y2AxisGreen, Z2AxisGreen);
	int Origin2Blue = Cube.SumOfThreeColors(X2AxisBlue, Y2AxisBlue, Z2AxisBlue);
	int Origin3Red = Cube.SumOfThreeColors(X3AxisRed, Y3AxisRed, Z3AxisRed);
	int Origin3Green = Cube.SumOfThreeColors(X3AxisGreen, Y3AxisGreen, Z3AxisGreen);
	int Origin3Blue = Cube.SumOfThreeColors(X3AxisBlue, Y3AxisBlue, Z3AxisBlue);
	switch(Mode[0]) {
	case 0:
		// Draw the X1 axis
		for (int X = 0; X < 8; X++) {
			if (Erase) {
				Cube.SetLEDColor(X, Y1AxisPosition, Z1AxisPosition, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X, Y1AxisPosition, Z1AxisPosition, X1AxisRed, X1AxisGreen, X1AxisBlue);
			}
		}
		// Draw the Y1 axis
		for (int Y = 0; Y < 8; Y++) {
			if (Erase) {
				Cube.SetLEDColor(X1AxisPosition, Y, Z1AxisPosition, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X1AxisPosition, Y, Z1AxisPosition, Y1AxisRed, Y1AxisGreen, Y1AxisBlue);
			}
		}
		// Draw the Z1 axis
		for (int Z = 0; Z < 8; Z++) {
			if (Erase) {
				Cube.SetLEDColor(X1AxisPosition, Y1AxisPosition, Z, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X1AxisPosition, Y1AxisPosition, Z, Z1AxisRed, Z1AxisGreen, Z1AxisBlue);
			}
		}
		// Draw the 1origin
		if (!Erase) {
			Cube.SetLEDColor(X1AxisPosition, Y1AxisPosition, Z1AxisPosition, Origin1Red, Origin1Green, Origin1Blue);
		}
		break;
	case 1:
		// Draw the X1 plane
		for (int X = 0; X < 8; X++) {
			for (int Y = 0; Y < 8; Y++) {
				if (Erase) {
					Cube.SetLEDColor(X, Y, Z1AxisPosition, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y, Z1AxisPosition, X1AxisRed, X1AxisGreen, X1AxisBlue);
				}
			}
		}
		// Draw the Y1 plane
		for (int Y = 0; Y < 8; Y++) {
			for (int Z = 0; Z < 8; Z++) {
				if (Erase) {
					Cube.SetLEDColor(X1AxisPosition, Y, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X1AxisPosition, Y, Z, X1AxisRed, X1AxisGreen, X1AxisBlue);
				}
			}
		}
		// Draw the Z1 plane
		for (int Z = 0; Z < 8; Z++) {
			for (int X = 0; X < 8; X++) {
				if (Erase) {
					Cube.SetLEDColor(X, Y1AxisPosition, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y1AxisPosition, Z, Z1AxisRed, Z1AxisGreen, Z1AxisBlue);
				}
			}
		}
		break;
	}
	if (NumberOfAxisSets < 2) return;
	switch (Mode[1]) {
	case 0:
		// Draw the X2 axis
		for (int X = 0; X < 8; X++) {
			if (Erase) {
				Cube.SetLEDColor(X, Y2AxisPosition, Z2AxisPosition, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X, Y2AxisPosition, Z2AxisPosition, X2AxisRed, X2AxisGreen, X2AxisBlue);
			}
		}
		// Draw the Y2 axis
		for (int Y = 0; Y < 8; Y++) {
			if (Erase) {
				Cube.SetLEDColor(X2AxisPosition, Y, Z2AxisPosition, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X2AxisPosition, Y, Z2AxisPosition, Y2AxisRed, Y2AxisGreen, Y2AxisBlue);
			}
		}
		// Draw the Z2 axis
		for (int Z = 0; Z < 8; Z++) {
			if (Erase) {
				Cube.SetLEDColor(X2AxisPosition, Y2AxisPosition, Z, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X2AxisPosition, Y2AxisPosition, Z, Z2AxisRed, Z2AxisGreen, Z2AxisBlue);
			}
		}
		// Draw the 2origin
		if (!Erase) {
			Cube.SetLEDColor(X2AxisPosition, Y2AxisPosition, Z2AxisPosition, Origin2Red, Origin2Green, Origin2Blue);
		}
		break;
	case 1:
		// Draw the X2 plane
		for (int X = 0; X < 8; X++) {
			for (int Y = 0; Y < 8; Y++) {
				if (Erase) {
					Cube.SetLEDColor(X, Y, Z2AxisPosition, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y, Z2AxisPosition, X2AxisRed, X2AxisGreen, X2AxisBlue);
				}
			}
		}
		// Draw the Y2 plane
		for (int Y = 0; Y < 8; Y++) {
			for (int Z = 0; Z < 8; Z++) {
				if (Erase) {
					Cube.SetLEDColor(X2AxisPosition, Y, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X2AxisPosition, Y, Z, X2AxisRed, X2AxisGreen, X2AxisBlue);
				}
			}
		}
		// Draw the Z2 plane
		for (int Z = 0; Z < 8; Z++) {
			for (int X = 0; X < 8; X++) {
				if (Erase) {
					Cube.SetLEDColor(X, Y2AxisPosition, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y2AxisPosition, Z, Z2AxisRed, Z2AxisGreen, Z2AxisBlue);
				}
			}
		}
		break;
	}
	if (NumberOfAxisSets < 3) return;
	switch (Mode[2]) {
	case 0:
		// Draw the X3 axis
		for (int X = 0; X < 8; X++) {
			if (Erase) {
				Cube.SetLEDColor(X, Y3AxisPosition, Z3AxisPosition, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X, Y3AxisPosition, Z3AxisPosition, X3AxisRed, X3AxisGreen, X3AxisBlue);
			}
		}
		// Draw the Y3 axis
		for (int Y = 0; Y < 8; Y++) {
			if (Erase) {
				Cube.SetLEDColor(X3AxisPosition, Y, Z3AxisPosition, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X3AxisPosition, Y, Z3AxisPosition, Y3AxisRed, Y3AxisGreen, Y3AxisBlue);
			}
		}
		// Draw the Z3 axis
		for (int Z = 0; Z < 8; Z++) {
			if (Erase) {
				Cube.SetLEDColor(X3AxisPosition, Y3AxisPosition, Z, 0, 0, 0);
			} else {
				Cube.SetLEDColor(X3AxisPosition, Y3AxisPosition, Z, Z3AxisRed, Z3AxisGreen, Z3AxisBlue);
			}
		}
		// Draw the 3origin
		if (!Erase) {
			Cube.SetLEDColor(X3AxisPosition, Y3AxisPosition, Z3AxisPosition, Origin3Red, Origin3Green, Origin3Blue);
		}
		break;
	case 1:
		// Draw the X3 plane
		for (int X = 0; X < 8; X++) {
			for (int Y = 0; Y < 8; Y++) {
				if (Erase) {
					Cube.SetLEDColor(X, Y, Z3AxisPosition, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y, Z3AxisPosition, X3AxisRed, X3AxisGreen, X3AxisBlue);
				}
			}
		}
		// Draw the Y3 plane
		for (int Y = 0; Y < 8; Y++) {
			for (int Z = 0; Z < 8; Z++) {
				if (Erase) {
					Cube.SetLEDColor(X3AxisPosition, Y, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X3AxisPosition, Y, Z, X3AxisRed, X3AxisGreen, X3AxisBlue);
				}
			}
		}
		// Draw the Z3 plane
		for (int Z = 0; Z < 8; Z++) {
			for (int X = 0; X < 8; X++) {
				if (Erase) {
					Cube.SetLEDColor(X, Y3AxisPosition, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y3AxisPosition, Z, Z3AxisRed, Z3AxisGreen, Z3AxisBlue);
				}
			}
		}
		break;
	}
}