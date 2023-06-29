// LEDWaterfall.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDWaterfall.h"

extern LEDCube Cube;
extern LEDWaterfall Waterfall;

LEDWaterfall::LEDWaterfall() {

}

int LEDWaterfall::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDWaterfall::StartWaterfall() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(80, 90));
	NumberOfCyclesToPerform = random(100, 150);
	CycleCounter = 0;
	for (SegmentNumber = 1; SegmentNumber < 11; SegmentNumber++) {
		SegmentColors[SegmentNumber][0] = 0;
		SegmentColors[SegmentNumber][1] = 0;
		SegmentColors[SegmentNumber][2] = 0;
	}
	SegmentColors[0][0] = Cube.RandomColor();
	SegmentColors[0][1] = Cube.RandomColor();
	SegmentColors[0][2] = Cube.RandomColor();
}

void LEDWaterfall::StepWaterfall() {
	CycleCounter++;
	if( CycleCounter >= NumberOfCyclesToPerform){
		StartWaterfall();
	}

	// Show segment 0
	Cube.SetLEDColor(3, 3, 7, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);
	Cube.SetLEDColor(4, 3, 7, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);
	Cube.SetLEDColor(3, 4, 7, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);
	Cube.SetLEDColor(4, 4, 7, SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2]);

	// Show segment 1
	for (X = 2; X < 6; X++) {
		if ((X == 2) || (X == 5)) {
			for (Y = 2; Y < 6; Y++) {
				Cube.SetLEDColor(X, Y, 7, SegmentColors[1][0], SegmentColors[1][1], SegmentColors[1][2]);
			}
		} else {
			Cube.SetLEDColor(X, 2, 7, SegmentColors[1][0], SegmentColors[1][1], SegmentColors[1][2]);
			Cube.SetLEDColor(X, 5, 7, SegmentColors[1][0], SegmentColors[1][1], SegmentColors[1][2]);
		}
	}

	// Show segment 2
	for (X = 1; X < 7; X++) {
		if ((X == 1) || (X == 6)) {
			for (Y = 1; Y < 7; Y++) {
				Cube.SetLEDColor(X, Y, 7, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
			}
		} else {
			Cube.SetLEDColor(X, 1, 7, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
			Cube.SetLEDColor(X, 6, 7, SegmentColors[2][0], SegmentColors[2][1], SegmentColors[2][2]);
		}
	}

	// Show segments 3 through 10
	for (SegmentNumber = 3; SegmentNumber < 11; SegmentNumber++) {
		LayerNumber = 10 - SegmentNumber;
		for (X = 0; X < 8; X++) {
			if ((X == 0) || (X == 7)) {
				for (Y = 0; Y < 8; Y++) {
					Cube.SetLEDColor(X, Y, LayerNumber, SegmentColors[SegmentNumber][0], SegmentColors[SegmentNumber][1], SegmentColors[SegmentNumber][2]);
				}
			} else {
				Cube.SetLEDColor(X, 0, LayerNumber, SegmentColors[SegmentNumber][0], SegmentColors[SegmentNumber][1], SegmentColors[SegmentNumber][2]);
				Cube.SetLEDColor(X, 7, LayerNumber, SegmentColors[SegmentNumber][0], SegmentColors[SegmentNumber][1], SegmentColors[SegmentNumber][2]);
			}
		}
	}

	// Roll the colors
	for (SegmentNumber = 10; SegmentNumber > 0; SegmentNumber--) {
		SegmentColors[SegmentNumber][0] = SegmentColors[SegmentNumber - 1][0];
		SegmentColors[SegmentNumber][1] = SegmentColors[SegmentNumber - 1][1];
		SegmentColors[SegmentNumber][2] = SegmentColors[SegmentNumber - 1][2];
	}
	int NewColor = Cube.NearbyColor(SegmentColors[0][0], SegmentColors[0][1], SegmentColors[0][2], 1);
	SegmentColors[0][0] = Cube.RedPartOf(NewColor);
	SegmentColors[0][1] = Cube.GreenPartOf(NewColor);
	SegmentColors[0][2] = Cube.BluePartOf(NewColor);
}
