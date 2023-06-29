// LEDDash.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDDash.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDDash Dash;

LEDDash::LEDDash() {

}

int LEDDash::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDDash::StartDash() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	NumberOfStepsToPerform = random(100, 500);
	// Cube.SetAnimationStepSpeedPeriodTo(100);
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	// Cube.SetAnimationStepSpeedPeriodTo(5000 / NumberOfStepsToPerform);
	StepCounter = 0;
	// Initialize elements to "off"
	for (int i = 0; i < TrailLength; i++) {
		Trail[i][9] = 0;
	}
	// Pick a width
	TrailWidth = random(1, 4);
	// Initialize color to white
	LeadRed = 7;
	LeadGreen = 7;
	LeadBlue = 7;
	// Tell Move our object size has a radius of 1
	Move.InitializeCubeMove(1);
}

void LEDDash::StepDash() {
	// Erase previous tail position
	DrawTrailElement(TrailLength-1, 0, 0, 0);
	// Determine next lead position
	StepCounter++;
	if (Move.AtEndOfCurrentCubeMoveSegment()) {
		if (StepCounter >= NumberOfStepsToPerform) {
			StartDash();
			return;
		}
		Move.SetupNextCubeMoveSegment();
		Move.StartCubeMoveSegment();
	} else {
		Move.AdvanceToNextCubeMovePosition();
	}
	// Update all the trailing position, direction and initialized flag bytes
	for (int i = TrailLength - 1; i > 0; i--) {
		Trail[i][0] = Trail[i-1][0];
		Trail[i][1] = Trail[i-1][1];
		Trail[i][2] = Trail[i-1][2];
		Trail[i][6] = Trail[i-1][6];
		Trail[i][7] = Trail[i-1][7];
		Trail[i][8] = Trail[i-1][8];
		Trail[i][9] = Trail[i-1][9];
	}
	// Get the position of the new lead element
	Trail[0][0] = Move.GetCurrentCubeMoveX();
	Trail[0][1] = Move.GetCurrentCubeMoveY();
	Trail[0][2] = Move.GetCurrentCubeMoveZ();
	// Vary the color of the lead element
	if ((StepCounter % StepsPerColorChange) == 2) {
		LeadRed = random(5, 8);
		LeadGreen = random(5, 8);
		LeadBlue = random(5, 8);
	}
	// Get the direction bytes of the new lead element
	Trail[0][6] = Move.GetCubeMoveDeltaX();
	Trail[0][7] = Move.GetCubeMoveDeltaY();
	Trail[0][8] = Move.GetCubeMoveDeltaZ();
	// Set the color of the lead element
	Trail[0][3] = LeadRed;
	Trail[0][4] = LeadGreen;
	Trail[0][5] = LeadBlue;
	// Declare the new lead element to be initialized
	Trail[0][9] = 1;
	// Fill the trailing elements with increasingly dimmer versions of the lead element
	int Red = LeadRed;
	int Green = LeadGreen;
	int Blue = LeadBlue;
	for (int i = 1; i < TrailLength; i++) {
		Trail[i][3] = Red;
		Trail[i][4] = Green;
		Trail[i][5] = Blue;
		if ((i % StepsPerDim) == 0) {
			Red = max(0, Red - 1);
			Green = max(0, Green - 1);
			Blue = max(0, Blue - 1);
		}
	}
	// Draw all the new elements
	for (int i = 0; i < TrailLength; i++) {
		DrawTrailElement(i, Trail[i][3], Trail[i][4], Trail[i][5]);
	}
}

void LEDDash::DrawTrailElement(int Index, int Red, int Green, int Blue) {
	// If this element hasn't yet been initialized, skip it
	if (Trail[Index][9] == 0) return;
	// Draw the corner LED
	Cube.SetLEDColor(Trail[Index][0], Trail[Index][1], Trail[Index][2], Red, Green, Blue);
	// Get particulars of the center motion when this element was first drawn
	int DX = Trail[Index][6];
	int DY = Trail[Index][7];
	int DZ = Trail[Index][8];
	// Get the directions from the current element's corner LED toward the center of the LED cube
	int WX = Cube.CenterBias(Trail[Index][0]);
	int WY = Cube.CenterBias(Trail[Index][1]);
	int WZ = Cube.CenterBias(Trail[Index][2]);
	// Draw the wings
	int WingWidth = 1;
	while (WingWidth < TrailWidth) {
		if (DX != 0) {
			// Center motion is in X direction so wings go in Y and Z directions
			Cube.SetLEDColor(Trail[Index][0], Trail[Index][1] + WY*WingWidth, Trail[Index][2], Red, Green, Blue);
			Cube.SetLEDColor(Trail[Index][0], Trail[Index][1], Trail[Index][2] + WZ*WingWidth, Red, Green, Blue);
		}
		if (DY != 0) {
			// Center motion is in Y direction so wings go in X and Z directions
			Cube.SetLEDColor(Trail[Index][0] + WX*WingWidth, Trail[Index][1], Trail[Index][2], Red, Green, Blue);
			Cube.SetLEDColor(Trail[Index][0], Trail[Index][1], Trail[Index][2] + WZ*WingWidth, Red, Green, Blue);
		}
		if (DZ != 0) {
			// Center motion is in Z direction so wings go in X and Y directions
			Cube.SetLEDColor(Trail[Index][0] + WX*WingWidth, Trail[Index][1], Trail[Index][2], Red, Green, Blue);
			Cube.SetLEDColor(Trail[Index][0], Trail[Index][1] + WY*WingWidth, Trail[Index][2], Red, Green, Blue);
		}
		WingWidth++;
	}
}
