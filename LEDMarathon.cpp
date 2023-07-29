// LEDMarathon.cpp
#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDMarathon.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDMarathon Marathon;

LEDMarathon::LEDMarathon() {

}

int LEDMarathon::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDMarathon::StartMarathon() {
	int Index;
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	StepTarget = random(1000, 2000);
	ColorChangeCounter = 0;
	ColorChangeTarget = random(25, 75);
	DirectionChangeCounter = 0;
	DirectionChangeTarget = random(100, 300);
	Direction = random(0, 6);
	LeadCompositeColor = Cube.RandomSolidColor();
	LeadRed = Cube.RedPartOf(LeadCompositeColor);
	LeadGreen = Cube.GreenPartOf(LeadCompositeColor);
	LeadBlue = Cube.BluePartOf(LeadCompositeColor);
	for (Index = 0; Index < MarathonTrailLength; Index++) {
		// Initialize the trail to "off at origin"
		Trail[Index][0] = 0;
		Trail[Index][1] = 0;
		Trail[Index][2] = 0;
		Trail[Index][3] = 0;
		Trail[Index][4] = 0;
		Trail[Index][5] = 0;
	}
	Cube.SetAnimationStepSpeedPeriodTo(random(25, 50));
	Move.InitializeMarathonMove();
}

void LEDMarathon::StepMarathon() {
	int Index;
	int RootX;
	int RootY;
	int RootZ;
	int RotatedX;
	int RotatedY;
	int RotatedZ;
	StepCounter++;
	if (StepCounter > StepTarget) {
		StartMarathon();
	}
	// Erase the previous last LED in the trail
	Cube.SetLEDColor(Trail[MarathonTrailLength-1][0], Trail[MarathonTrailLength-1][1], Trail[MarathonTrailLength-1][2], 0, 0, 0);
	// Shift the trail positions 1 notch
	for (Index = MarathonTrailLength - 1; Index > 0; Index--) {
		Trail[Index][0] = Trail[Index-1][0];
		Trail[Index][1] = Trail[Index-1][1];
		Trail[Index][2] = Trail[Index-1][2];
	}
	// Get the new position of the lead element
	Move.StepMarathonMove();
	RootX = Move.GetMarathonMoveX();
	RootY = Move.GetMarathonMoveY();
	RootZ = Move.GetMarathonMoveZ();
	// Is it time to change orientation?
	DirectionChangeCounter++;
	if (DirectionChangeCounter >= DirectionChangeTarget) {
		DirectionChangeCounter = 0;
		Direction = Cube.RandomButDifferent(Direction, 0, 6);
	}
	switch (Direction) {
	case 0:
		// Z is the normal (unrotated orientation)
		RotatedX = RootX;
		RotatedY = RootY;
		RotatedZ = RootZ;
		break;
	case 1:
		// Like 0 but rotate backward
		RotatedX = 7 - RootX;
		RotatedY = 7 - RootY;
		RotatedZ = RootZ;
		break;
	case 2:
		// Swap Y & Z
		RotatedX = RootX;
		RotatedY = RootZ;
		RotatedZ = RootY;
		break;
	case 3:
		// Like 2 but rotate backward
		RotatedX = 7 - RootX;
		RotatedY = RootZ;
		RotatedZ = 7 - RootY;
		break;
	case 4:
		// Swap X & Z
		RotatedX = RootZ;
		RotatedY = RootY;
		RotatedZ = RootX;
		break;
	case 5:
		// Like 4 but rotate backward
		RotatedX = RootZ;
		RotatedY = 7 - RootY;
		RotatedZ = 7 - RootX;
		break;
	}
	Trail[0][0] = RotatedX;
	Trail[0][1] = RotatedY;
	Trail[0][2] = RotatedZ;
	// Is it time to pick up a new color for the lead element?
	ColorChangeCounter++;
	if (ColorChangeCounter >= ColorChangeTarget) {
		ColorChangeCounter = 0;
		LeadCompositeColor = Cube.RandomSolidColor();
		LeadRed = Cube.RedPartOf(LeadCompositeColor);
		LeadGreen = Cube.GreenPartOf(LeadCompositeColor);
		LeadBlue = Cube.BluePartOf(LeadCompositeColor);
	}
	// Fill in the color of the new lead and draw it
	Trail[0][3] = LeadRed;
	Trail[0][4] = LeadGreen;
	Trail[0][5] = LeadBlue;
	Cube.SetLEDColor(Trail[0][0], Trail[0][1], Trail[0][2], Trail[0][3], Trail[0][4], Trail[0][5]);
	// Fill in the colors of the trail elements, dimming as we go, and draw each one
	int Red = LeadRed;
	int Green = LeadGreen;
	int Blue = LeadBlue;
	for (Index = 1; Index < MarathonTrailLength; Index++) {
		if ((Index % MarathonStepsPerDim) == 1) {
			Red = max(0, Red - 1);
			Green = max(0, Green - 1);
			Blue = max(0, Blue - 1);
		}
		Trail[Index][3] = Red;
		Trail[Index][4] = Green;
		Trail[Index][5] = Blue;
		Cube.SetLEDColor(Trail[Index][0], Trail[Index][1], Trail[Index][2], Trail[Index][3], Trail[Index][4], Trail[Index][5]);
	}
}
