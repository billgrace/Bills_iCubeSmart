// LEDCorner.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCorner.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCorner Corner;

LEDCorner::LEDCorner() {

}

int LEDCorner::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCorner::StartCorner() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(80, 130));
	StepCounter = 0;
	StepTarget = random(100, 300);
	NumberOfCorners = random(2, 9);
	StartTarget = 50 - 2 * NumberOfCorners;
	StartCounter = 0;
	for (int i = 0; i < NumberOfCorners; i++) {
		// Set all corner numbers to -1 indicating "off"
		Corner[i][0] = -1;
	}
	// ... then start with one corner right away
	StartACorner();
}

void LEDCorner::StepCorner() {
	int NewCompositeColor;
	int c;
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartCorner();
	}
	// First update each active corner
	for (c = 0; c < NumberOfCorners; c++) {
		if (Corner[c][0] > -1) {
			// This corner is active
			if (Corner[c][4] == Corner[c][7]) {
				// This corner is already at its final size,
				//  ... increment the number of steps it's been here
				Corner[c][9]++;
				if (Corner[c][9] >= Corner[c][8]) {
					// This corner has finished its final size persistence
					//  so erase it and
					DrawCorner(Corner[c][0], Corner[c][4], 0, 0, 0);
					//  then de-activate it.
					//  (... erase must come first since it requires the cube corner number
					//        which gets set to -1 to de-activate!)
					Corner[c][0] = -1;
				} else {
					// So, we're persisting at the final size - use the size
					//   ... change counter to vary the color
					Corner[c][6]++;
					if (Corner[c][6] >= Corner[c][5]) {
						// Time to change the color
						Corner[c][6] = 0;
						NewCompositeColor = Cube.NearbyColor(Corner[c][1], Corner[c][2], Corner[c][3], 1);
						Corner[c][1] = Cube.RedPartOf(NewCompositeColor);
						Corner[c][2] = Cube.GreenPartOf(NewCompositeColor);
						Corner[c][3] = Cube.BluePartOf(NewCompositeColor);
					}
				}
			} else {
				// This corner is still growing
				// ... increment the number of steps it's been at this size
				Corner[c][6]++;
				if (Corner[c][6] >= Corner[c][5]) {
					// It's time to grow so reset the counter and bump the size
					Corner[c][6] = 0;
					Corner[c][4]++;
				}
			}
		}
	}
	// Then check to see if it's time to start a new one
	StartCounter++;
	if (StartCounter >= StartTarget) {
		StartACorner();
	}
	// Finally, draw each active corner
	for (c = 0; c < NumberOfCorners; c++) {
		if (-1 != Corner[c][0]) {
			DrawCorner(Corner[c][0], Corner[c][4], Corner[c][1], Corner[c][2], Corner[c][3]);
		}
	}
}

void LEDCorner::StartACorner() {
	// First, find an available array element
	int NewCornerIndex = -1;
	for (int i = 0; i < NumberOfCorners; i++) {
		if (Corner[i][0] == -1) {
			NewCornerIndex = i;
			break;
		}
	}
	if (NewCornerIndex == -1) {
		// We didn't find an available array element so give up
		return;
	}
	// OK, we've got an array element, now find a cube corner that's not in use
	int AvailableCubeCorner = -1;
	int AttemptCounter = 0;
	int TentativeCubeCorner;
	bool AlreadyInUse;
	while ((AvailableCubeCorner == -1) && (AttemptCounter < 20)) {
		// Take up to 20 tries
		AttemptCounter++;
		// Pick a random cube corner
		TentativeCubeCorner = random(0, 8);
		// Run through the corner array to see if this one is already in use
		AlreadyInUse = false;
		for (int c = 0; c < NumberOfCorners; c++) {
			if (Corner[c][0] == TentativeCubeCorner) {
				AlreadyInUse = true;
				break;
			}
		}
		// Is this random tentative choice still looking available?
		if (false == AlreadyInUse) {
			// Yes!
			AvailableCubeCorner = TentativeCubeCorner;
		}
	}
	if (-1 != AvailableCubeCorner) {
		// OK, we found an available spot so it's OK to start up a new cube there.
		Corner[NewCornerIndex][0] = AvailableCubeCorner;
		Corner[NewCornerIndex][1] = Cube.RandomColor();
		Corner[NewCornerIndex][2] = Cube.RandomColor();
		Corner[NewCornerIndex][3] = Cube.RandomColor();
		Corner[NewCornerIndex][4] = 1; // Always start with a single LED in the corner
		Corner[NewCornerIndex][5] = random(15, 30); // How many steps at each size
		Corner[NewCornerIndex][6] = 1; // Already 1 done since we'll paint the start in this routine
		Corner[NewCornerIndex][7] = random(2, 4); // Final size
		Corner[NewCornerIndex][8] = random(30, 100); // How many steps to persist at the final size
		Corner[NewCornerIndex][9] = 0; // Count of how many steps at the final size
		DrawCorner(NewCornerIndex, 1, Corner[NewCornerIndex][1], Corner[NewCornerIndex][2], Corner[NewCornerIndex][3]);
	}
}

void LEDCorner::DrawCorner(int CornerNumber, int Size, int Red, int Green, int Blue) {
	int X;
	int Y;
	int Z;
// 8 Corners are numbered:
// Corner#	X	Y	Z
// 0		0	0	0
// 1		7	0	0
// 2		0	7	0
// 3		7	7	0
// 4		0	0	7
// 5		7	0	7
// 6		0	7	7
// 7		7	7	7
	switch (CornerNumber) {
	case 0:
		for (X = 0; X < Size; X++) {
			for (Y = 0; Y < Size; Y++) {
				for (Z = 0; Z < Size; Z++) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 1:
		for (X = 7; X > (7 - Size); X--) {
			for (Y = 0; Y < Size; Y++) {
				for (Z = 0; Z < Size; Z++) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 2:
		for (X = 0; X < Size; X++) {
			for (Y = 7; Y > (7 - Size); Y--) {
				for (Z = 0; Z < Size; Z++) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 3:
		for (X = 7; X > (7 - Size); X--) {
			for (Y = 7; Y > (7 - Size); Y--) {
				for (Z = 0; Z < Size; Z++) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 4:
		for (X = 0; X < Size; X++) {
			for (Y = 0; Y < Size; Y++) {
				for (Z = 7; Z > (7 - Size); Z--) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 5:
		for (X = 7; X > (7 - Size); X--) {
			for (Y = 0; Y < Size; Y++) {
				for (Z = 7; Z > (7 - Size); Z--) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 6:
		for (X = 0; X < Size; X++) {
			for (Y = 7; Y > (7 - Size); Y--) {
				for (Z = 7; Z > (7 - Size); Z--) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	case 7:
		for (X = 7; X > (7 - Size); X--) {
			for (Y = 7; Y > (7 - Size); Y--) {
				for (Z = 7; Z > (7 - Size); Z--) {
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
		break;
	}
}
