// LEDSprinkler.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDSprinkler.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDSprinkler Sprinkler;

LEDSprinkler::LEDSprinkler() {

}

int LEDSprinkler::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDSprinkler::StartSprinkler() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(5, 10));
	StepCounter = 0;
	StepTarget = random(500, 800);
	for (int corner = 0; corner < 4; corner++) {
		for (int direction = 0; direction < 3; direction++) {
			Arc[corner][direction][0] = Cube.RandomColor();
			Arc[corner][direction][1] = Cube.RandomColor();
			Arc[corner][direction][2] = Cube.RandomColor();
			Arc[corner][direction][3] = 0;
		}
	}
	CurrentCorner = 0;
	CurrentDirection = 0;
}

void LEDSprinkler::StepSprinkler() {
	int Stage;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartSprinkler();
	}
	// Go around all corners and directions,
	//  one corner/direction combination on each pass and
	//  for each one, erase the present arc, step to the next stage and
	//  draw the new arc.
	Stage = Arc[CurrentCorner][CurrentDirection][3];
	// .... erase present arc
	DrawArc(CurrentCorner, CurrentDirection, Stage, true);
	// .... move to next arc stage
	Stage = Cube.NextIndex(Stage, 3);
	// .... draw new arc
	DrawArc(CurrentCorner, CurrentDirection, Stage, false);
	// Save the new stage
	Arc[CurrentCorner][CurrentDirection][3] = Stage;
	// Increment Corner/Direction for next time
	CurrentDirection++;
	if (CurrentDirection >= 3) {
		CurrentDirection = 0;
		CurrentCorner++;
		if (CurrentCorner >= 4) {
			CurrentCorner = 0;
		}
	}
}

void LEDSprinkler::DrawArc(int Corner, int Direction, int Stage, bool Erase) {
	int Red;
	int Green;
	int Blue;
	int ArcCoordinate0X;
	int ArcCoordinate0Z;
	int ArcCoordinate1X;
	int ArcCoordinate1Z;
	int ArcCoordinate2X;
	int ArcCoordinate2Z;
	int Drop0X;
	int Drop0Y;
	int Drop0Z;
	int Drop1X;
	int Drop1Y;
	int Drop1Z;
	int Drop2X;
	int Drop2Y;
	int Drop2Z;
	// Figure the color values
	if (Erase == true) {
		Red = 0;
		Green = 0;
		Blue = 0;
	} else {
		Red = Arc[Corner][Direction][0];
		Green = Arc[Corner][Direction][1];
		Blue = Arc[Corner][Direction][2];
	}
	// Pick up the generic arc coordinates.
	ArcCoordinate0X = Move.GetSprinklerArcPosition0(Stage);
	ArcCoordinate0Z = Move.GetSprinklerArcPosition1(Stage);
	ArcCoordinate1X = Move.GetSprinklerArcPosition0(Stage+3);
	ArcCoordinate1Z = Move.GetSprinklerArcPosition1(Stage+3);
	ArcCoordinate2X = Move.GetSprinklerArcPosition0(Stage+6);
	ArcCoordinate2Z = Move.GetSprinklerArcPosition1(Stage+6);
	// The [][1] or 'Z' or 'vertical' coordinate is always valid without any mapping while
	//   the [][0] or horizontal coordinate needs to be mapped for each arc.
	Drop0Z = ArcCoordinate0Z;
	Drop1Z = ArcCoordinate1Z;
	Drop2Z = ArcCoordinate2Z;
	switch (Corner) {
	case 0:
		// Front left top corner
		switch (Direction) {
		case 0:
			// toward the right along the front side (+X, Y=0)
			Drop0X = ArcCoordinate0X;
			Drop0Y = 0;
			Drop1X = ArcCoordinate1X;
			Drop1Y = 0;
			Drop2X = ArcCoordinate2X;
			Drop2Y = 0;
			break;
		case 1:
			// diagonal between the front and left sides (+X, +Y)
			Drop0X = ArcCoordinate0X;
			Drop0Y = ArcCoordinate0X;
			Drop1X = ArcCoordinate1X;
			Drop1Y = ArcCoordinate1X;
			Drop2X = ArcCoordinate2X;
			Drop2Y = ArcCoordinate2X;
			break;
		case 2:
			// toward the back along the left side (X=0, +Y)
			Drop0X = 0;
			Drop0Y = ArcCoordinate0X;
			Drop1X = 0;
			Drop1Y = ArcCoordinate1X;
			Drop2X = 0;
			Drop2Y = ArcCoordinate2X;
			break;
		}
		break;
	case 1:
		// Front right top corner
		switch (Direction) {
		case 0:
			// toward the back along the right side (X=7, +Y)
			Drop0X = 7;
			Drop0Y = ArcCoordinate0X;
			Drop1X = 7;
			Drop1Y = ArcCoordinate1X;
			Drop2X = 7;
			Drop2Y = ArcCoordinate2X;
			break;
		case 1:
			// diagonal between the right and front sides (-X, +Y)
			Drop0X = 7 - ArcCoordinate0X;
			Drop0Y = ArcCoordinate0X;
			Drop1X = 7 - ArcCoordinate1X;
			Drop1Y = ArcCoordinate1X;
			Drop2X = 7 - ArcCoordinate2X;
			Drop2Y = ArcCoordinate2X;
			break;
		case 2:
			// toward the left along the front side (-X, Y=0)
			Drop0X = 7 - ArcCoordinate0X;
			Drop0Y = 0;
			Drop1X = 7 - ArcCoordinate1X;
			Drop1Y = 0;
			Drop2X = 7 - ArcCoordinate2X;
			Drop2Y = 0;
			break;
		}
		break;
	case 2:
		// Left rear top corner
		switch (Direction) {
		case 0:
			// toward the front along the left side (X=0, -Y)
			Drop0X = 0;
			Drop0Y = 7 - ArcCoordinate0X;
			Drop1X = 0;
			Drop1Y = 7 - ArcCoordinate1X;
			Drop2X = 0;
			Drop2Y = 7 - ArcCoordinate2X;
			break;
		case 1:
			// diagonal between the back and left sides (+X, -Y)
			Drop0X = ArcCoordinate0X;
			Drop0Y = 7 - ArcCoordinate0X;
			Drop1X = ArcCoordinate1X;
			Drop1Y = 7 - ArcCoordinate1X;
			Drop2X = ArcCoordinate2X;
			Drop2Y = 7 - ArcCoordinate2X;
			break;
		case 2:
			// toward the right along the back side (+X, Y=7)
			Drop0X = ArcCoordinate0X;
			Drop0Y = 7;
			Drop1X = ArcCoordinate1X;
			Drop1Y = 7;
			Drop2X = ArcCoordinate2X;
			Drop2Y = 7;
			break;
		}
		break;
	case 3:
		// Right rear top corner
		switch (Direction) {
		case 0:
			// toward the left along the back side (-X, Y=7)
			Drop0X = 7 - ArcCoordinate0X;
			Drop0Y = 7;
			Drop1X = 7 - ArcCoordinate1X;
			Drop1Y = 7;
			Drop2X = 7 - ArcCoordinate2X;
			Drop2Y = 7;
			break;
		case 1:
			// diagonal between the back and right sides (-X, -Y)
			Drop0X = 7 - ArcCoordinate0X;
			Drop0Y = 7 - ArcCoordinate0X;
			Drop1X = 7 - ArcCoordinate1X;
			Drop1Y = 7 - ArcCoordinate1X;
			Drop2X = 7 - ArcCoordinate2X;
			Drop2Y = 7 - ArcCoordinate2X;
			break;
		case 2:
			// toward the front along the right side (X=7, -Y)
			Drop0X = 7;
			Drop0Y = 7 - ArcCoordinate0X;
			Drop1X = 7;
			Drop1Y = 7 - ArcCoordinate1X;
			Drop2X = 7;
			Drop2Y = 7 - ArcCoordinate2X;
			break;
		}
		break;
	}
	// Draw the three drops
	Cube.SetLEDColor(Drop0X, Drop0Y, Drop0Z, Red, Green, Blue);
	Cube.SetLEDColor(Drop1X, Drop1Y, Drop1Z, Red, Green, Blue);
	Cube.SetLEDColor(Drop2X, Drop2Y, Drop2Z, Red, Green, Blue);
}
