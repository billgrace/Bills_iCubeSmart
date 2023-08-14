// LEDWorms.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDWorms.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDWorms Worms;

LEDWorms::LEDWorms () {

}

int LEDWorms::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDWorms::StartWorms() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	NumberOfWorms = random(1, LEDWormMaximumNumberOfWorms + 1);
	Cube.SetAnimationStepSpeedPeriodTo(random(200, 350)/NumberOfWorms);
	StepCounter = 0;
	StepTarget = random(100, 160) * NumberOfWorms;
	CurrentWorm = 0;
	for (int i = 0; i < NumberOfWorms; i++) {
		StartAWorm(i);
	}
}

void LEDWorms::StepWorms() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartWorms();
	}
	// for (int i = 0; i < NumberOfWorms; i++) {
	// 	EraseLastSegment(i);
	// 	AddNewHeadSegment(i);
	// 	DrawWorm(i);
	// }
	EraseLastSegment(CurrentWorm);
	AddNewHeadSegment(CurrentWorm);
	DrawWorm(CurrentWorm);
	CurrentWorm++;
	if (CurrentWorm >= NumberOfWorms) {
		CurrentWorm = 0;
	}
}

void LEDWorms::StartAWorm(int WormIndex) {
	// Pick a starting worm segment's position and color
	WormSegment[WormIndex][0][0] = random(1, 7);
	WormSegment[WormIndex][0][1] = random(1, 7);
	WormSegment[WormIndex][0][2] = random(1, 7);
	WormSegment[WormIndex][0][3] = Cube.RandomColor();
	WormSegment[WormIndex][0][4] = Cube.RandomColor();
	WormSegment[WormIndex][0][5] = Cube.RandomColor();
	// Initialize starting length, maximum length & direction of motion
	WormParameters[WormIndex][0] = 1;
	WormParameters[WormIndex][1] = random(LEDWormMaximumWormLength / 2, LEDWormMaximumWormLength + 1);
	WormParameters[WormIndex][2] = random(0, 6);
	DrawWorm(WormIndex);
}

void LEDWorms::AddNewHeadSegment(int WormIndex) {
	int OldHeadX;
	int OldHeadY;
	int OldHeadZ;
	int NewHeadX;
	int NewHeadY;
	int NewHeadZ;
	int OldDirection;
	int NewDirection;
	OldHeadX = WormSegment[WormIndex][0][0];
	OldHeadY = WormSegment[WormIndex][0][1];
	OldHeadZ = WormSegment[WormIndex][0][2];
	// (MOST of the new axis coordinates will be the same as the old ones)
	NewHeadX = OldHeadX;
	NewHeadY = OldHeadY;
	NewHeadZ = OldHeadZ;
	OldDirection = WormParameters[WormIndex][2];
	// Continue in the previous direction if possible, otherwise pick a new one
	switch (OldDirection) {
	case 0:
		// +X
		if (OldHeadX < random(4, 8)) {
			// Still room in the +X direction
			NewDirection = OldDirection;
		} else {
			// Need to change direction
			NewDirection = PickANewDirection(0, OldHeadX, OldHeadY, OldHeadZ);
		}
		break;
	case 1:
		// -X
		if (OldHeadX > random(0, 4)) {
			// Still room in the -X direction
			NewDirection = OldDirection;
		} else {
			// Need to change direction
			NewDirection = PickANewDirection(1, OldHeadX, OldHeadY, OldHeadZ);
		}
		break;
	case 2:
		// +Y
		if (OldHeadY < random(4, 8)) {
			// Still room in the +Y direction
			NewDirection = OldDirection;
		} else {
			// Need to change direction
			NewDirection = PickANewDirection(2, OldHeadX, OldHeadY, OldHeadZ);
		}
		break;
	case 3:
		// -Y
		if (OldHeadY > random(0, 4)) {
			// Still room in the -Y direction
			NewDirection = OldDirection;
		} else {
			// Need to change direction
			NewDirection = PickANewDirection(3, OldHeadX, OldHeadY, OldHeadZ);
		}
		break;
	case 4:
		// +Z
		if (OldHeadZ < random(4, 8)) {
			// Still room in the +Z direction
			NewDirection = OldDirection;
		} else {
			// Need to change direction
			NewDirection = PickANewDirection(4, OldHeadX, OldHeadY, OldHeadZ);
		}
		break;
	case 5:
		// -Z
		if (OldHeadZ > random(0, 4)) {
			// Still room in the -Z direction
			NewDirection = OldDirection;
		} else {
			// Need to change direction
			NewDirection = PickANewDirection(5, OldHeadX, OldHeadY, OldHeadZ);
		}
		break;
	}
	// Figure the location of the new head segment
	switch (NewDirection) {
	case 0:
		NewHeadX = OldHeadX + 1;
		break;
	case 1:
		NewHeadX = OldHeadX - 1;
		break;
	case 2:
		NewHeadY = OldHeadY + 1;
		break;
	case 3:
		NewHeadY = OldHeadY - 1;
		break;
	case 4:
		NewHeadZ = OldHeadZ + 1;
		break;
	case 5:
		NewHeadZ = OldHeadZ - 1;
		break;
	}
	// Shift the segment info down the line
	if (WormParameters[WormIndex][0] == 1) {
		// If the worm is only 1 segment long, explicitly shift 1st segment to 2nd
		WormSegment[WormIndex][1][0] = WormSegment[WormIndex][0][0];
		WormSegment[WormIndex][1][1] = WormSegment[WormIndex][0][1];
		WormSegment[WormIndex][1][2] = WormSegment[WormIndex][0][2];
		WormSegment[WormIndex][1][3] = WormSegment[WormIndex][0][3];
		WormSegment[WormIndex][1][4] = WormSegment[WormIndex][0][4];
		WormSegment[WormIndex][1][5] = WormSegment[WormIndex][0][5];
	} else {
		// otherwise the worm is long enough to use a for loop to shift the segments
		for (int s = WormParameters[WormIndex][0]; s > 0; s--) {
			WormSegment[WormIndex][s][0] = WormSegment[WormIndex][s - 1][0];
			WormSegment[WormIndex][s][1] = WormSegment[WormIndex][s - 1][1];
			WormSegment[WormIndex][s][2] = WormSegment[WormIndex][s - 1][2];
			WormSegment[WormIndex][s][3] = WormSegment[WormIndex][s - 1][3];
			WormSegment[WormIndex][s][4] = WormSegment[WormIndex][s - 1][4];
			WormSegment[WormIndex][s][5] = WormSegment[WormIndex][s - 1][5];
		}
	}
	// Increment the worm length if it's not yet full length
	if (WormParameters[WormIndex][0] < WormParameters[WormIndex][1]) {
		WormParameters[WormIndex][0]++;
	}
	// Add the new head segment
	WormSegment[WormIndex][0][0] = NewHeadX;
	WormSegment[WormIndex][0][1] = NewHeadY;
	WormSegment[WormIndex][0][2] = NewHeadZ;
	// Save the new direction
	WormParameters[WormIndex][2] = NewDirection;
}

void LEDWorms::EraseLastSegment(int WormIndex) {
	int WormLength;
	int X;
	int Y;
	int Z;
	// If this worm has not yet reached full length, skip erasing its last segment
	if (WormParameters[WormIndex][0] < WormParameters[WormIndex][1]) {
		return;
	}
	WormLength = WormParameters[WormIndex][0]; 
	X = WormSegment[WormIndex][WormLength - 1][0];
	Y = WormSegment[WormIndex][WormLength - 1][1];
	Z = WormSegment[WormIndex][WormLength - 1][2];
	Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
}

int LEDWorms::PickANewDirection(int OldDirection, int OldHeadX, int OldHeadY, int OldHeadZ) {
	// Allow a few attempts to find a new direction that will work
	int AttemptsLeft = 5;
	bool FoundAViableDirection = false;
	int CandidateNewDirection;
	while ((AttemptsLeft > 0) && (FoundAViableDirection == false)) {
		// First pick a candidate new direction that's not the old direction or its reverse
		switch (OldDirection) {
		case 0:
			CandidateNewDirection = Cube.RandomPickOfFour(2, 3, 4, 5);
			break;
		case 1:
			CandidateNewDirection = Cube.RandomPickOfFour(2, 3, 4, 5);
			break;
		case 2:
			CandidateNewDirection = Cube.RandomPickOfFour(0, 1, 4, 5);
			break;
		case 3:
			CandidateNewDirection = Cube.RandomPickOfFour(0, 1, 4, 5);
			break;
		case 4:
			CandidateNewDirection = Cube.RandomPickOfFour(0, 1, 2, 3);
			break;
		case 5:
			CandidateNewDirection = Cube.RandomPickOfFour(0, 1, 2, 3);
			break;
		}
		// Now check to see if the new direction has room to grow
		switch (CandidateNewDirection) {
		case 0:
			if (OldHeadX < 7) {
				FoundAViableDirection = true;
			}
			break;
		case 1:
			if (OldHeadX > 0) {
				FoundAViableDirection = true;
			}
			break;
		case 2:
			if (OldHeadY < 7) {
				FoundAViableDirection = true;
			}
			break;
		case 3:
			if (OldHeadY > 0) {
				FoundAViableDirection = true;
			}
			break;
		case 4:
			if (OldHeadZ < 7) {
				FoundAViableDirection = true;
			}
			break;
		case 5:
			if (OldHeadZ > 0) {
				FoundAViableDirection = true;
			}
			break;
		}
		AttemptsLeft--;
	}
	// Just in case the random attempts above ALL failed... fall back on simply
	//  reversing the previous direction
	if (FoundAViableDirection == false) {
		switch (OldDirection) {
		case 0:
			CandidateNewDirection = 1;
			break;
		case 1:
			CandidateNewDirection = 0;
			break;
		case 2:
			CandidateNewDirection = 3;
			break;
		case 3:
			CandidateNewDirection = 2;
			break;
		case 4:
			CandidateNewDirection = 5;
			break;
		case 5:
			CandidateNewDirection = 4;
			break;
		}
	}
	return CandidateNewDirection;
}


void LEDWorms::DrawWorm(int WormIndex) {

	// Serial1.print("DrawWorm(");
	// Serial1.print(WormIndex);
	// Serial1.println(")");

	for (int i = 0; i < WormParameters[WormIndex][0]; i++) {
		Cube.SetLEDColor(WormSegment[WormIndex][i][0], WormSegment[WormIndex][i][1], WormSegment[WormIndex][i][2],
							WormSegment[WormIndex][i][3], WormSegment[WormIndex][i][4], WormSegment[WormIndex][i][5]);
	}
}

