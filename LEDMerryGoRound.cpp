// LEDMerryGoRound.cpp
#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDMerryGoRound.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDMerryGoRound MerryGoRound;

LEDMerryGoRound::LEDMerryGoRound() {

}

int LEDMerryGoRound::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDMerryGoRound::StartMerryGoRound() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(50, 100));
	StepCounter = 0;
	StepTarget = random(100, 150);
	MoveCounter = 0;
	MoveTarget = random(10, 15);
	EdgeSize = random(1, 4);
	// 1, 2, 4 are OK - let's skip 3
	// NumberOfHorsies = Cube.RandomButDifferent(3, 1, MerryGoRoundMaximumNumberOfHorsies + 1);
	NumberOfHorsies = 4;
	// Might as well initialize all of them...
	for (int i = 0; i < MerryGoRoundMaximumNumberOfHorsies; i++) {
		Horsie[i][0] = random(1, 3);
		Horsie[i][1] = random(Horsie[i][0] + 3, 8);
		Horsie[i][2] = random(Horsie[i][0], Horsie[i][1]);
		Horsie[i][3] = Cube.RandomPickOfTwo(-1, 1);
		Horsie[i][4] = Cube.RandomColor();
		Horsie[i][5] = Cube.RandomColor();
		Horsie[i][6] = Cube.RandomColor();
	}
	Move.InitializeMerryGoRoundMove(EdgeSize);
}

void LEDMerryGoRound::StepMerryGoRound() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartMerryGoRound();
	}
	// Time to rotate?
	MoveCounter++;
	if (MoveCounter >= MoveTarget) {
		MoveCounter = 0;
		// Erase presently-positioned horsies
		DrawHorsies(true);
		// Increment the rotaty position
		Move.StepMerryGoRoundMove();
	}
	// Update the heights of the horsies
	for (int h = 0; h < NumberOfHorsies; h++) {
		switch (Horsie[h][3]) {
		case -1:
			// Going down
			if (Horsie[h][2] == Horsie[h][0]) {
				// Already at the bottom so turn around & head up
				Horsie[h][3] = 1;
			} else {
				// Not yet at the bottom so move down
				Horsie[h][2]--;
			}
			break;
		case 1:
			// Going up
			if (Horsie[h][2] == Horsie[h][1]) {
				// Already at the top so turn around & head down
				Horsie[h][3] = -1;
			} else {
				// Not yet at the top so move up
				Horsie[h][2]++;
			}
			break;
		}
	}
	// Draw the horsies
	DrawHorsies(false);
}

void LEDMerryGoRound::DrawHorsies(bool Erase) {
	// Pre-figure the X,Y for all four possible horsies
	int Xs[4];
	int Ys[4];
	// ... first horsie takes the Move. root position
	Xs[0] = Move.GetMerryGoRoundMoveX();
	Ys[0] = Move.GetMerryGoRoundMoveY();
	// ... second horsie is directly opposite the first
	Xs[1] = 8 - Xs[0] - EdgeSize;
	Ys[1] = 8 - Ys[0] - EdgeSize;
	// ... third and fourth horsies are "rotated 90 degrees"
	Xs[2] = 8 - Ys[0] - EdgeSize;
	Ys[2] = Xs[0];
	Xs[3] = 8 - Xs[2] - EdgeSize;
	Ys[3] = 8 - Ys[2] - EdgeSize;
	for (int h = 0; h < NumberOfHorsies; h++) {
		if (Erase) {
			DrawHorsie(Xs[h], Ys[h], Horsie[h][2], 0, 0, 0);
		} else {
			DrawHorsie(Xs[h], Ys[h], Horsie[h][2], Horsie[h][4], Horsie[h][5], Horsie[h][6]);
		}
	}
}

void LEDMerryGoRound::DrawHorsie(int Left, int Front, int HorsieHeight, int Red, int Green, int Blue) {
	// Draw the horsie from bottom to top and erase the space above the top
	for (int Z = 0; Z < CubeHeight; Z++) {
		for (int X = Left; X < (Left + EdgeSize); X++) {
			for (int Y = Front; Y < (Front + EdgeSize); Y++) {
				if (Z > HorsieHeight) {
					// Erase the space above
					Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
				} else {
					// Draw the horse
					Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
				}
			}
		}
	}
}