// LEDFace.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDFace.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDFace Face;

LEDFace::LEDFace() {

}

int LEDFace::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDFace::StartFace() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(20, 50));
	StepCounter = 0;
	StepTarget = random(500, 1500);
	StartNewCounter = 0;
	StartNewTarget = random(40, 100);
	Mode = random(0, 2);
	// Set all the cubes in the data array to "available"
	for (int i = 0; i < LEDFaceMaxNumberOfCubes; i++) {
		FaceCube[i][17] = 0;
	}
	StartANewFaceCube();
}

void LEDFace::StepFace() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartFace();
	}
	StartNewCounter++;
	if (StartNewCounter >= StartNewTarget) {
		StartNewCounter = 0;
		StartANewFaceCube();
	}
	for (int i = 0; i < LEDFaceMaxNumberOfCubes; i++) {
		// Give each active cube a processing turn
		if (FaceCube[i][17] != 0) {
			DrawCube(i);
		}
	}
}

void LEDFace::StartANewFaceCube() {
	int OffsetMax;
	int EdgeLength;
	int X;
	int Y;
	int Z;
	int CompositeColor;
	// Find an available cube element in the data array
	for (int c = 0; c < LEDFaceMaxNumberOfCubes; c++) {
		if (FaceCube[c][17] == 0) {
			// This array element is available
			// Set brightness animation to "getting brighter from dimmest"
			FaceCube[c][13] = 1;
			FaceCube[c][14] = 1;
			// Assign the six face orientations in a random-ish order
			AssignFaceOrientations(c);
			// Locate the current cube within the LED cube (left, front, bottom corner)
			EdgeLength = random(3, 9);
			FaceCube[c][6] = EdgeLength;
			OffsetMax = 8 - EdgeLength;
			X = random(0, OffsetMax + 1);
			Y = random(0, OffsetMax + 1);
			Z = random(0, OffsetMax + 1);
			FaceCube[c][7] = X;
			FaceCube[c][8] = Y;
			FaceCube[c][9] = Z;
			// Pick a primary color for the cube
			CompositeColor = Cube.RandomSolidColor();
			FaceCube[c][10] = Cube.RedPartOf(CompositeColor);
			FaceCube[c][11] = Cube.GreenPartOf(CompositeColor);
			FaceCube[c][12] = Cube.BluePartOf(CompositeColor);
			// Always start with the first face
			FaceCube[c][15] = 0;
			// Pick a mode
			FaceCube[c][16] = random(0, 2);
			// FaceCube[c][16] = Mode;
			// FaceCube[c][16] = 0;
			// Mark this array element as active
			FaceCube[c][17] = 1;
			// Exit the for loop so we only start *ONE* cube
			break;
		}
	}
}

void LEDFace::AssignFaceOrientations(int CubeIndex) {
	int i;
	int j;
	int k;
	int l;
	// First assign orientations in numerical order and THEN scramble
	//  them around a bit by swapping them a few times.
	// (doing it this way avoids the need to come up with some super-clever way
	//   to get all six orientations more-or-less-randomly distributed among
	//    all six array elements)
	for (i = 0; i < 6; i++) {
		// This makes the initial in-numerical-order assignment
		FaceCube[CubeIndex][i] = i;
	}
	for (i = 0; i < 10; i++) {
		// This makes 10 passes of scrambling
		j = random(0, 6); // This picks one array element at random
		k = Cube.RandomButDifferent(j, 0, 6); // This picks one of the other array elements
		l = FaceCube[CubeIndex][j]; // This saves the orientation of array element j
		FaceCube[CubeIndex][j] = FaceCube[CubeIndex][k]; // This swaps element k's orientation into element j
		FaceCube[CubeIndex][k] = l; // This swaps elements j's original orientation into element k
	}
	// ... and we leave with all six orientations scattered among the six array elements
}

void LEDFace::DrawCube(int CubeIndex) {
	int CurrentBrightness;
	int BrightnessDelta;
	int CurrentFace;
	CurrentBrightness = FaceCube[CubeIndex][13];
	BrightnessDelta = FaceCube[CubeIndex][14];
	CurrentFace = FaceCube[CubeIndex][15];
	// First draw the current face at the current brightness
	DrawFace(CubeIndex, CurrentFace);
	// Then figure the next face/brightness
	//  (Mode determines the sequence: faces per brightness or brightnesses per face)
	switch (FaceCube[CubeIndex][16]) {
	case 0:
		// Process all faces at each brightness
		CurrentFace++;
		if (CurrentFace > 5) {
			// We've done all 6 faces at this brightness so move to the next brightness
			CurrentFace = 0;
			if (BrightnessDelta == 1) {
				// We're getting brighter
				if (CurrentBrightness == 7) {
					// We're already at the maximum brightness so turn around and get dimmer
					BrightnessDelta = -1;
					CurrentBrightness = 6;
				} else {
					// We can still get brighter...
					CurrentBrightness++;
				}
			} else {
				// We're getting dimmer
				if (CurrentBrightness == 0) {
					// We're already at the minimum brightness
					// If we just dimmed to zero brightness we need to explicily
					//  erase the cube...
					if (CurrentBrightness == 0) {
						FaceCube[CubeIndex][13] = 0;
						for (int f = 0; f < 6; f++) {
							DrawFace(CubeIndex, f);
						}
					}
					// ...and mark is as available
					FaceCube[CubeIndex][17] = 0;
				} else {
					// We can still get dimmer...
					CurrentBrightness--;
				}
			}
		}
		break;
	case 1:
		// Run each face through the whole brightness range before moving to the next face
		if (BrightnessDelta == 1) {
			// Getting brighter
			if (CurrentBrightness >= 7) {
				// We're all the way bright on this face - move on
				if (CurrentFace >= 5) {
					// We've done all 6 faces so it's time to switch to dimming
					CurrentBrightness = 7;
					BrightnessDelta = -1;
					CurrentFace = 0;
				} else {
					// There are still more faces to bring from dim to bright
					CurrentBrightness = 1;
					CurrentFace++;
				}
			} else {
				// Still room to get brighter on this face
				CurrentBrightness++;
			}
		} else {
			// Getting dimmer
			if (CurrentBrightness > 0) {
				// Still room to get dimmer on this face
				CurrentBrightness--;
			} else {
				// Brightness is at zero - time to move to the next face
				CurrentFace++;
				if (CurrentFace > 5) {
					// We've done all 6 faces so this cube is finished
					// ... mark it as inactive and erase it just to be sure
					FaceCube[CubeIndex][17] = 0;
				} else {
					// The next face needs dimming - start at bright - 1
					CurrentBrightness = 6;
				}
			}
		}
		break;
	}
	// Save the updated brightness and current face
	FaceCube[CubeIndex][13] = CurrentBrightness;
	FaceCube[CubeIndex][14] = BrightnessDelta;
	FaceCube[CubeIndex][15] = CurrentFace;
}

void LEDFace::DrawFace(int CubeIndex, int FaceIndex) {
	// Draw a single cube face with the current brightness
	int X;
	int Y;
	int Z;
	int X1;
	int Y1;
	int Z1;
	int X2;
	int Y2;
	int Z2;
	int EdgeLength;
	int Red;
	int Green;
	int Blue;
	int DimmingFactor;
	int R;
	int G;
	int B;
	Red = FaceCube[CubeIndex][10];
	Green = FaceCube[CubeIndex][11];
	Blue = FaceCube[CubeIndex][12];
	DimmingFactor = 7 - FaceCube[CubeIndex][13];
	// Figure R, G and B given the current brightness
	//  (we're using a "solid" or "primary" color so each of Red, Green and Blue will be either 0 or 7)
	if (Red == 0) {
		R = 0;
	} else {
		R = Red - DimmingFactor;
	}
	if (Green == 0) {
		G = 0;
	} else {
		G = Green - DimmingFactor;
	}
	if (Blue == 0) {
		B = 0;
	} else {
		B = Blue - DimmingFactor;
	}
	// Figure the starting and ending coordinates for all edges
	EdgeLength = FaceCube[CubeIndex][6];
	X1 = FaceCube[CubeIndex][7];
	Y1 = FaceCube[CubeIndex][8];
	Z1 = FaceCube[CubeIndex][9];
	X2 = X1 + EdgeLength - 1;
	Y2 = Y1 + EdgeLength - 1;
	Z2 = Z1 + EdgeLength - 1;
	// Draw the face taking into account the face's orientation and position
	switch (FaceCube[CubeIndex][FaceIndex]) {
	case 0:
		// Vertical face parallel to right side of cube
		for (Y = Y1; Y <= Y2; Y++) {
			for (Z = Z1; Z <= Z2; Z++) {
				Cube.SetLEDColor(X2, Y, Z, R, G, B);
			}
		}
		break;
	case 1:
		// Vertical face parallel to left side of cube
		for (Y = Y1; Y <= Y2; Y++) {
			for (Z = Z1; Z <= Z2; Z++) {
				Cube.SetLEDColor(X1, Y, Z, R, G, B);
			}
		}
		break;
	case 2:
		// Vertical face parallel to back side of cube
		for (X = X1; X <= X2; X++) {
			for (Z = Z1; Z <= Z2; Z++) {
				Cube.SetLEDColor(X, Y2, Z, R, G, B);
			}
		}
		break;
	case 3:
		// Vertical face parallel to front side of cube
		for (X = X1; X <= X2; X++) {
			for (Z = Z1; Z <= Z2; Z++) {
				Cube.SetLEDColor(X, Y1, Z, R, G, B);
			}
		}
		break;
	case 4:
		// Horizontal face parallel to top side of cube
		for (X = X1; X <= X2; X++) {
			for (Y = Y1; Y <= Y2; Y++) {
				Cube.SetLEDColor(X, Y, Z2, R, G, B);
			}
		}
		break;
	case 5:
		// Horizontal face parallel to bottom side of cube
		for (X = X1; X <= X2; X++) {
			for (Y = Y1; Y <= Y2; Y++) {
				Cube.SetLEDColor(X, Y, Z1, R, G, B);
			}
		}
		break;
	}
}

