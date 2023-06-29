// LEDFountain.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDFountain.h"

extern LEDCube Cube;
extern LEDFountain Fountain;

LEDFountain::LEDFountain() {

}

int LEDFountain::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDFountain::StartFountain() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(100, 150));
	NumberOfCyclesToPerform = random(30, 50);
	CycleCounter = 0;
	for (SegmentNumber = 1; SegmentNumber < 18; SegmentNumber++) {
		SegmentColors[SegmentNumber][0] = 0;
		SegmentColors[SegmentNumber][1] = 0;
		SegmentColors[SegmentNumber][2] = 0;
	}
	SegmentColors[0][0] = Cube.RandomColor();
	SegmentColors[0][1] = Cube.RandomColor();
	SegmentColors[0][2] = Cube.RandomColor();
}

void LEDFountain::StepFountain() {
	CycleCounter++;
	if( CycleCounter >= NumberOfCyclesToPerform){
		StartFountain();
	}

	// Show segment 0
	for (X = 0; X < 8; X++) {
		if ((X == 0) || (X == 7)) {
			for (Y = 0; Y < 8; Y++) {
				Cube.SetLEDColor(X, Y, 0, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);
			}
		} else {
			Cube.SetLEDColor(X, 0, 0, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);
			Cube.SetLEDColor(X, 7, 0, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);
		}
	}

	// Show segment 1
	for (X = 1; X < 7; X++) {
		if ((X == 1) || (X == 6)) {
			for (Y = 1; Y < 7; Y++) {
				Cube.SetLEDColor(X, Y, 0, SegmentColors[1][0], SegmentColors[1][1], SegmentColors[1][2]);
			}
		} else {
			Cube.SetLEDColor(X, 1, 0, SegmentColors[1][0], SegmentColors[1][1], SegmentColors[1][2]);
			Cube.SetLEDColor(X, 6, 0, SegmentColors[1][0], SegmentColors[1][1], SegmentColors[1][2]);
		}
	}

	// Show segment 2
	for (X = 1; X < 7; X++) {
		if ((X == 1) || (X == 6)) {
			for (Y = 1; Y < 7; Y++) {
				Cube.SetLEDColor(X, Y, 1, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
			}
		} else {
			Cube.SetLEDColor(X, 1, 1, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
			Cube.SetLEDColor(X, 6, 1, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
		}
	}
	for (X = 2; X < 6; X++) {
		if ((X == 2) || (X == 5)) {
			for (Y = 2; Y < 6; Y++) {
				Cube.SetLEDColor(X, Y, 1, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
			}
		} else {
			Cube.SetLEDColor(X, 2, 1, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
			Cube.SetLEDColor(X, 5, 1, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
		}
	}

	// Show segment 3
	for (X = 2; X < 6; X++) {
		if ((X == 2) || (X == 5)) {
			for (Y = 2; Y < 6; Y++) {
				Cube.SetLEDColor(X, Y, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);
			}
		} else {
			Cube.SetLEDColor(X, 2, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);
			Cube.SetLEDColor(X, 5, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);
		}
	}
	Cube.SetLEDColor(3, 3, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);
	Cube.SetLEDColor(4, 3, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);
	Cube.SetLEDColor(3, 4, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);
	Cube.SetLEDColor(4, 4, 2, SegmentColors[3][0], SegmentColors[3][1], SegmentColors[3][2]);

	// Show segment 4
	Cube.SetLEDColor(3, 3, 3, SegmentColors[4][0], SegmentColors[4][1], SegmentColors[4][2]);
	Cube.SetLEDColor(4, 3, 3, SegmentColors[4][0], SegmentColors[4][1], SegmentColors[4][2]);
	Cube.SetLEDColor(3, 4, 3, SegmentColors[4][0], SegmentColors[4][1], SegmentColors[4][2]);
	Cube.SetLEDColor(4, 4, 3, SegmentColors[4][0], SegmentColors[4][1], SegmentColors[4][2]);

	// Show segment 5
	Cube.SetLEDColor(3, 3, 4, SegmentColors[5][0], SegmentColors[5][1], SegmentColors[5][2]);
	Cube.SetLEDColor(4, 3, 4, SegmentColors[5][0], SegmentColors[5][1], SegmentColors[5][2]);
	Cube.SetLEDColor(3, 4, 4, SegmentColors[5][0], SegmentColors[5][1], SegmentColors[5][2]);
	Cube.SetLEDColor(4, 4, 4, SegmentColors[5][0], SegmentColors[5][1], SegmentColors[5][2]);

	// Show segment 6
	Cube.SetLEDColor(3, 3, 5, SegmentColors[6][0], SegmentColors[6][1], SegmentColors[6][2]);
	Cube.SetLEDColor(4, 3, 5, SegmentColors[6][0], SegmentColors[6][1], SegmentColors[6][2]);
	Cube.SetLEDColor(3, 4, 5, SegmentColors[6][0], SegmentColors[6][1], SegmentColors[6][2]);
	Cube.SetLEDColor(4, 4, 5, SegmentColors[6][0], SegmentColors[6][1], SegmentColors[6][2]);

	// Show segment 7
	Cube.SetLEDColor(3, 3, 6, SegmentColors[7][0], SegmentColors[7][1], SegmentColors[7][2]);
	Cube.SetLEDColor(4, 3, 6, SegmentColors[7][0], SegmentColors[7][1], SegmentColors[7][2]);
	Cube.SetLEDColor(3, 4, 6, SegmentColors[7][0], SegmentColors[7][1], SegmentColors[7][2]);
	Cube.SetLEDColor(4, 4, 6, SegmentColors[7][0], SegmentColors[7][1], SegmentColors[7][2]);

	// Show segment 8
	Cube.SetLEDColor(3, 3, 7, SegmentColors[8][0], SegmentColors[8][1], SegmentColors[8][2]);
	Cube.SetLEDColor(4, 3, 7, SegmentColors[8][0], SegmentColors[8][1], SegmentColors[8][2]);
	Cube.SetLEDColor(3, 4, 7, SegmentColors[8][0], SegmentColors[8][1], SegmentColors[8][2]);
	Cube.SetLEDColor(4, 4, 7, SegmentColors[8][0], SegmentColors[8][1], SegmentColors[8][2]);

	// Show segment 9
	for (X = 2; X < 6; X++) {
		if ((X == 2) || (X == 5)) {
			for (Y = 2; Y < 6; Y++) {
				Cube.SetLEDColor(X, Y, 7, SegmentColors[9][0], SegmentColors[9][1], SegmentColors[9][2]);
			}
		} else {
			Cube.SetLEDColor(X, 2, 7, SegmentColors[9][0], SegmentColors[9][1], SegmentColors[9][2]);
			Cube.SetLEDColor(X, 5, 7, SegmentColors[9][0], SegmentColors[9][1], SegmentColors[9][2]);
		}
	}

	// Show segment 10
	for (X = 1; X < 7; X++) {
		if ((X == 1) || (X == 6)) {
			for (Y = 1; Y < 7; Y++) {
				Cube.SetLEDColor(X, Y, 7, SegmentColors[10][0], SegmentColors[10][1], SegmentColors[10][2]);
			}
		} else {
			Cube.SetLEDColor(X, 1, 7, SegmentColors[10][0], SegmentColors[10][1], SegmentColors[10][2]);
			Cube.SetLEDColor(X, 6, 7, SegmentColors[10][0], SegmentColors[10][1], SegmentColors[10][2]);
		}
	}

	// Show segment 11
	for (X = 0; X < 8; X++) {
		if ((X == 0) || (X == 7)) {
			for (Y = 0; Y < 8; Y++) {
				Cube.SetLEDColor(X, Y, 7, SegmentColors[11][0], SegmentColors[11][1], SegmentColors[11][2]);
			}
		} else {
			Cube.SetLEDColor(X, 0, 7, SegmentColors[11][0], SegmentColors[11][1], SegmentColors[11][2]);
			Cube.SetLEDColor(X, 7, 7, SegmentColors[11][0], SegmentColors[11][1], SegmentColors[11][2]);
		}
	}

	// Show segment 12 corners
	Cube.SetLEDColor(0, 0, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(0, 7, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(7, 0, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(7, 7, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	// Show segment 12 midpoints
	Cube.SetLEDColor(0, 2, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(0, 5, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(2, 0, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(5, 0, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(7, 2, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(7, 5, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(2, 7, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);
	Cube.SetLEDColor(5, 7, 6, SegmentColors[12][0], SegmentColors[12][1], SegmentColors[12][2]);

	// Show segment 13 corners
	Cube.SetLEDColor(0, 0, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(0, 7, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(7, 0, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(7, 7, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	// Show segment 12 midpoints
	Cube.SetLEDColor(0, 2, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(0, 5, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(2, 0, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(5, 0, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(7, 2, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(7, 5, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(2, 7, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);
	Cube.SetLEDColor(5, 7, 5, SegmentColors[13][0], SegmentColors[13][1], SegmentColors[13][2]);

	// Show segment 14 corners
	Cube.SetLEDColor(0, 0, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(0, 7, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(7, 0, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(7, 7, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	// Show segment 12 midpoints
	Cube.SetLEDColor(0, 2, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(0, 5, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(2, 0, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(5, 0, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(7, 2, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(7, 5, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(2, 7, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);
	Cube.SetLEDColor(5, 7, 4, SegmentColors[14][0], SegmentColors[14][1], SegmentColors[14][2]);

	// Show segment 15 corners
	Cube.SetLEDColor(0, 0, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(0, 7, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(7, 0, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(7, 7, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	// Show segment 12 midpoints
	Cube.SetLEDColor(0, 2, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(0, 5, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(2, 0, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(5, 0, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(7, 2, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(7, 5, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(2, 7, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);
	Cube.SetLEDColor(5, 7, 3, SegmentColors[15][0], SegmentColors[15][1], SegmentColors[15][2]);

	// Show segment 16 corners
	Cube.SetLEDColor(0, 0, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(0, 7, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(7, 0, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(7, 7, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	// Show segment 12 midpoints
	Cube.SetLEDColor(0, 2, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(0, 5, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(2, 0, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(5, 0, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(7, 2, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(7, 5, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(2, 7, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);
	Cube.SetLEDColor(5, 7, 2, SegmentColors[16][0], SegmentColors[16][1], SegmentColors[16][2]);

	// Show segment 17 corners
	Cube.SetLEDColor(0, 0, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(0, 7, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(7, 0, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(7, 7, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	// Show segment 12 midpoints
	Cube.SetLEDColor(0, 2, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(0, 5, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(2, 0, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(5, 0, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(7, 2, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(7, 5, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(2, 7, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);
	Cube.SetLEDColor(5, 7, 1, SegmentColors[17][0], SegmentColors[17][1], SegmentColors[17][2]);

	// Roll the colors
	for (SegmentNumber = 17; SegmentNumber > 0; SegmentNumber--) {
		SegmentColors[SegmentNumber][0] = SegmentColors[SegmentNumber - 1][0];
		SegmentColors[SegmentNumber][1] = SegmentColors[SegmentNumber - 1][1];
		SegmentColors[SegmentNumber][2] = SegmentColors[SegmentNumber - 1][2];
	}
	int NewColor = Cube.NearbyColor(SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2], 1);
	SegmentColors[0][0] = Cube.RedPartOf(NewColor);
	SegmentColors[0][1] = Cube.GreenPartOf(NewColor);
	SegmentColors[0][2] = Cube.BluePartOf(NewColor);
}
