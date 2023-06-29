// LEDStarrySky.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDStarrySky.h"

extern LEDCube Cube;
extern LEDStarrySky StarrySky;

LEDStarrySky::LEDStarrySky() {

}

int LEDStarrySky::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDStarrySky::StartStarrySky() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 50));
	NumberOfStars = 12;
	InitialTwinkleStagger = 11;
	StepCount = 0;
	IntroCount = NumberOfStars * InitialTwinkleStagger;
	MaxSteps = 300;
	TimeToQuit = false;
	for (X = 0; X < 8; X++){
		for (Y = 0; Y < 8; Y++){
			for (Z =0; Z < 8; Z++) {
				StarState[X][Y][Z] = 0;
			}
		}
	}
}

void LEDStarrySky::StepStarrySky() {
	int NewBrightness;
	StepCount++;
	if (StepCount <= IntroCount) {
		// We're still starting out so add new stars
		if (0 == (StepCount % InitialTwinkleStagger)) {
			// Meter how fast we add them so they don't all twinkle in synch
			XYZ = Cube.RandomPositionWhereLEDIsOff();
			StartAStarAt(Cube.XPartOf(XYZ), Cube.YPartOf(XYZ), Cube.ZPartOf(XYZ));
		}
	}
	// Scan and update all locations in the cube at each step
	for (X = 0; X < 8; X++) {
		for (Y = 0; Y < 8; Y++) {
			for (Z = 0; Z < 8; Z++) {
				if (false == TimeToQuit) {
					if (StarState[X][Y][Z] > 0) {
						// This location has a star in it so update the twinkle state.
						NewBrightness = NextStarBrightness(X, Y, Z);
						Cube.SetLEDColor(X, Y, Z, NewBrightness, NewBrightness, NewBrightness);
						if (NewBrightness == 0) {
							// We just extinguished the star at this location so...
							// IF we're not winding up, start a new star
							if(StepCount <= (MaxSteps + IntroCount)) {
								// Add a new star since we're not yet winding up and finishing
								XYZ = Cube.RandomPositionWhereLEDIsOff();
								StartAStarAt(Cube.XPartOf(XYZ), Cube.YPartOf(XYZ), Cube.ZPartOf(XYZ));
							} else {
								// We're finishing so don't add a new star AND quit if they're all gone now
								if (ArrayIsEmpty()) {
									TimeToQuit = true;
									Cube.IncrementAnimationDurationCycleCount();
								}
							}
						}
					}
				}
			}
		}
	}
}

bool LEDStarrySky::ArrayIsEmpty() {
	for (X = 0; X < 8; X++) {
		for (Y = 0; Y < 8; Y++) {
			for (Z =0; Z < 8; Z++) {
				if (StarState[X][Y][Z] > 0) {
					return false;
				}
			}
		}
	}
	return true;
}

int LEDStarrySky::NextStarBrightness(int X, int Y, int Z) {
	int ReturnValue;
	int NewState;
	switch(StarState[X][Y][Z]) {
	case 0:
		ReturnValue = 1;
		NewState = 1;
		break;
	case 1:
		ReturnValue = 2;
		NewState = 2;
		break;
	case 2:
		ReturnValue = 3;
		NewState = 3;
		break;
	case 3:
		ReturnValue = 4;
		NewState = 4;
		break;
	case 4:
		ReturnValue = 5;
		NewState = 5;
		break;
	case 5:
		ReturnValue = 6;
		NewState = 6;
		break;
	case 6:
		ReturnValue = 7;
		NewState = 7;
		break;
	case 7:
		ReturnValue = 7;
		NewState = 8;
		break;
	case 8:
		ReturnValue = 6;
		NewState = 9;
		break;
	case 9:
		ReturnValue = 5;
		NewState = 10;
		break;
	case 10:
		ReturnValue = 4;
		NewState = 11;
		break;
	case 11:
		ReturnValue = 3;
		NewState = 12;
		break;
	case 12:
		ReturnValue = 2;
		NewState = 13;
		break;
	case 13:
		ReturnValue = 1;
		NewState = 14;
		break;
	case 14:
		ReturnValue = 0;
		NewState = 0;
		break;
	default:
		ReturnValue = 0;
		NewState = 0;
		break;
	}
	StarState[X][Y][Z] = NewState;
	return ReturnValue;
}

void LEDStarrySky::StartAStarAt(int X, int Y, int Z) {
	StarState[X][Y][Z] = 1;
	Cube.SetLEDColor(X, Y, Z, 1, 1, 1);
}
