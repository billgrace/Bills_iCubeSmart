// LEDBarGraph.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDBarGraph.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDBarGraph BarGraph;

LEDBarGraph::LEDBarGraph() {

}

int LEDBarGraph::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDBarGraph::StartBarGraph() {
	int Index;
	int Row;
	int Column;
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	// Pick a bar size
	switch(random( 0, 2)) {
	case 0:
		BarsInUse = 16;
		EdgeSize = 2;
		BarsPerAxis = 4;
		StepTarget = random(200, 400);
		Cube.SetAnimationStepSpeedPeriodTo(random(80, 150));
		break;
	case 1:
		BarsInUse = 4;
		EdgeSize = 4;
		BarsPerAxis = 2;
		StepTarget = random(100, 300);
		Cube.SetAnimationStepSpeedPeriodTo(random(100, 200));
		break;
	}
	// Initialize bar locations
	Index = 0;
	for (Row = 0; Row < BarsPerAxis; Row++) {
		for (Column = 0; Column < BarsPerAxis; Column++) {
			Bar[Index][0] = Row * EdgeSize;
			Bar[Index][1] = Column * EdgeSize;
			Index++;
		}
	}
	CurrentRow = random(0, 2);
	CurrentColumn = random(0, 2);
	// Mode = random(0, 4);
	Mode = 0;
	MinTopLevel = random(1, 4);
	MoveOnCounter = 0;
	// Set all bars to inactive
	for (Index = 0; Index < BarsInUse; Index++) {
		Bar[Index][7] = 0;
	}
	// Initialize active bars
	switch(Mode) {
	case 0:
		// Only single bars moving - start a single bar
		MoveOnTarget = random(10, 20);
		Index = random(0, 16);
		StartBar(Index);
		break;
	case 1:
		// All bars moving - start all bars
		MoveOnTarget = random(20, 70);
		for (Index = 0; Index < BarsInUse; Index++) {
			StartBar(Index);
		}
		break;
	case 2:
		// One row of bars moving - pick a row and start all columns in that row
		MoveOnTarget = random(20, 40);
		Row = random(0, BarsPerAxis);
		for (Column = 0; Column < BarsPerAxis; Column++) {
			Index = Row * BarsPerAxis + Column;
			StartBar(Index);
		}
		break;
	case 3:
		// One column of bars moving - pick a column and start all rows in that column
		MoveOnTarget = random(20, 40);
		Column = random(0, BarsPerAxis);
		for (Row = 0; Row < BarsPerAxis; Row++) {
			Index = Row * BarsPerAxis + Column;
			StartBar(Index);
		}
		break;
	}
}

void LEDBarGraph::StepBarGraph() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartBarGraph();
	}
	for (int b = 0; b < BarsInUse; b++) {
		if (Bar[b][7] > 0) {
			MoveBar(b);
		}
	}
}

void LEDBarGraph::StartBar(int Index) {
	// X and Y are fixed
	// Grab random colors
	Bar[Index][2] = Cube.RandomColor();
	Bar[Index][3] = Cube.RandomColor();
	Bar[Index][4] = Cube.RandomColor();
	// Pick a random maximum level
	Bar[Index][5] = random(MinTopLevel + 1, 8);
	// Start at the minimum level
	Bar[Index][6] = MinTopLevel;
	// Start off going up
	Bar[Index][7] = 1;
	// Draw the bar up to its present level
	for (int l = 0; l <= Bar[Index][6]; l++) {
		DrawBarLevel(Index, l, false);
	}
}

void LEDBarGraph::MoveBar(int Index) {
	// This test is probably not necessary....
	if (0 == Bar[Index][7]) {
		// This bar is not active - shouldn't have gotten to this point!
		return;
	}
	if (1 == Bar[Index][7]) {
		// This bar is still going up
		if (Bar[Index][6] >= Bar[Index][5]) {
			// OK, we're at the top so...
			// Head back down
			Bar[Index][7] = 2;
			// Erase the top level
			DrawBarLevel(Index, Bar[Index][6], true);
			// Update the current top level
			Bar[Index][6]--;
		} else {
			// Not yet at the top so go up a notch
			Bar[Index][6]++;
			DrawBarLevel(Index, Bar[Index][6], false);
		}
	} else {
		// This bar is going down
		if (Bar[Index][6] <= MinTopLevel) {
			// OK, we're at the bottom so re-start...
			//  ... this bar unless we're in Mode == 0
			if (0 == Mode) {
				// We're in the one-bar-at-a-time mode so turn off this bar and
				// then start up another one.
				Bar[Index][7] = 0;
				StartBar(random(0, BarsInUse));
			} else {
				// We're in one of the multi-bar modes so just restart this one
				StartBar(Index);
			}
		} else {
			// Not at the bottom yet so move down a level
			DrawBarLevel(Index, Bar[Index][6], true);
			Bar[Index][6]--;
		}
	}
}

void LEDBarGraph::DrawBarLevel(int Index, int Level, bool Erase) {
	int AnchorX;
	int AnchorY;
	int Red;
	int Green;
	int Blue;
	AnchorX = Bar[Index][0];
	AnchorY = Bar[Index][1];
	if (Erase) {
		Red = 0;
		Green = 0;
		Blue = 0;
	} else {
		Red = Bar[Index][2];
		Green = Bar[Index][3];
		Blue = Bar[Index][4];
	}
	for (int i = 0; i < EdgeSize; i++) {
		for (int j = 0; j < EdgeSize; j++) {
			Cube.SetLEDColor(AnchorX + i, AnchorY + j, Level, Red, Green, Blue);
		}
	}
}
