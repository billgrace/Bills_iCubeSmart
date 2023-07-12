// LEDSlosh.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDSlosh.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDSlosh Slosh;

LEDSlosh::LEDSlosh() {
}

int LEDSlosh::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDSlosh::StartSlosh() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	FastPeriod = random(10, 20);
	Cube.SetAnimationStepSpeedPeriodTo(FastPeriod);
	Move.InitializeSloshMove();
	Mode = random(0, 2);
	StepCounter = 0;
	StepTarget = random(200, 500);
	LeadRed = Cube.RandomColor();
	LeadGreen = Cube.RandomColor();
	LeadBlue = Cube.RandomColor();
	TailRed = Cube.RandomColor();
	TailGreen = Cube.RandomColor();
	TailBlue = Cube.RandomColor();
	LeadX = 7;
	LeadZ = 0;
	Stage = 0;
	// Start with the tail empty
	for (int TailPosition = 0; TailPosition < 10; TailPosition++) {
		for (int Coordinate = 0; Coordinate < 3; Coordinate++) {
			TailCoordinates[TailPosition][Coordinate] = 0;
		}
	}
}

void LEDSlosh::StepSlosh() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartSlosh();
	}
	// Erase the existing slosh
	DrawSlosh(false);
	// Shift the tail coordinate array for all segments except the new lead
	for (int TailIndex = 9; TailIndex > 0; TailIndex--) {
		TailCoordinates[TailIndex][0] = TailCoordinates[TailIndex-1][0];
		TailCoordinates[TailIndex][1] = TailCoordinates[TailIndex-1][1];
		TailCoordinates[TailIndex][2] = TailCoordinates[TailIndex-1][2];
	}
	// Put the previous lead into the tail coordinate array's first spot
	TailCoordinates[0][0] = LeadX;
	TailCoordinates[0][1] = LeadZ;
	// Mark this tail position as no longer empty
	TailCoordinates[0][2] = 1;
	// Move to the next position
	Cube.SetAnimationStepSpeedPeriodTo(FastPeriod * Move.GetSloshM());
	Move.StepSloshMove();
	// Check if it's time to move to the other side
	if (Move.SloshIsAtBeginning()) {
		Stage = Cube.NextIndex(Stage, 2);
	}
	// Figure the new lead position
	switch(Stage) {
	case 0:
		LeadX = Move.GetSloshX();
		LeadZ = Move.GetSloshZ();
		break;
	case 1:
		LeadX = 7 - Move.GetSloshX();
		LeadZ = Move.GetSloshZ();
		break;
	}
	// Draw the new slosh
	DrawSlosh(true);
}

void LEDSlosh::DrawSlosh(bool OffOn) {
	if (OffOn) {
		// draw the new slosh
		DrawSegment(LeadX, LeadZ, LeadRed, LeadGreen, LeadBlue);
		for (int TailIndex = 0; TailIndex < 10; TailIndex++) {
			if (TailCoordinates[TailIndex][2] > 0) {
				DrawSegment(TailCoordinates[TailIndex][0], TailCoordinates[TailIndex][1], TailRed, TailGreen, TailBlue);
			}
		}
	} else {
		// erase the previous slosh
		Cube.SetLEDColor(LeadX, 0, LeadZ, 0, 0, 0);
		for (int TailIndex = 0; TailIndex < 10; TailIndex++) {
			if (TailCoordinates[TailIndex][2] > 0) {
				DrawSegment(TailCoordinates[TailIndex][0], TailCoordinates[TailIndex][1], 0, 0, 0);
			}
		}
	}
}

void LEDSlosh::DrawSegment(int X, int Z, int Red, int Green, int Blue) {
	for (int Y = 0; Y < 8; Y++) {
		switch (Mode) {
		case 0:
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			break;
		case 1:
			Cube.SetLEDColor(Y, X, Z, Red, Green, Blue);
			break;
		}
	}
}

