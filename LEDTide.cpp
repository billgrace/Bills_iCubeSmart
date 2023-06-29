// LEDTide.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDTide.h"

extern LEDCube Cube;
extern LEDTide Tide;

LEDTide::LEDTide(){
}

int LEDTide::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDTide::StartTide() {
	InitializeTwinkleCount();
	LevelStepDirection = 1;
	SolidLevel = 0;
	TwinkleLevel = 1;
	LevelColor[0][0] = Cube.RandomColor();
	LevelColor[0][1] = Cube.RandomColor();
	LevelColor[0][2] = Cube.RandomColor();
	for (int Level = 1; Level < 8; Level++) {
		int ThisLevelCompositeColor = Cube.NearbyColor(LevelColor[Level-1][0], LevelColor[Level-1][1], LevelColor[Level-1][2], 1);
		LevelColor[Level][0] = Cube.RedPartOf(ThisLevelCompositeColor);
		LevelColor[Level][1] = Cube.GreenPartOf(ThisLevelCompositeColor);
		LevelColor[Level][2] = Cube.BluePartOf(ThisLevelCompositeColor);
	}
	Cube.ClearImage();
	Cube.FillLayer(SolidLevel, LevelColor[SolidLevel][0], LevelColor[SolidLevel][1], LevelColor[SolidLevel][2]);
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(4, 15));
}

void LEDTide::InitializeTwinkleCount() {
	TwinkleStepCount = random(64, 100);
	CleanupX = 0;
	CleanupY = 0;
}

void LEDTide::CleanupNext() {
	// When a level switches from twinkle to solid on the way up or twinkle to dark on the way down,
	//  update the stragglers.
	bool GotOne = false;
	if (LevelStepDirection == 1) {
		// We're moving up - turn on any that are off in the new solid layer
		CleanupZ = SolidLevel;
		if (false == Cube.ThisLEDIsOn(CleanupX, CleanupY, CleanupZ)) {
			// Turn this one on and we're done
			Cube.SetLEDColor(CleanupX, CleanupY, CleanupZ, LevelColor[SolidLevel][0], LevelColor[SolidLevel][1], LevelColor[SolidLevel][2]);
			GotOne = true; // (not really necessary given the if/then/else but I'm a nevous old coder....)
		} else {
			// This one is already on - look further
			while ((GotOne == false) && NextCleanupPosition()) {
				// Try this new position
				if (false == Cube.ThisLEDIsOn(CleanupX, CleanupY, CleanupZ)) {
					// Turn it on
					Cube.SetLEDColor(CleanupX, CleanupY, CleanupZ, LevelColor[SolidLevel][0], LevelColor[SolidLevel][1], LevelColor[SolidLevel][2]);
					GotOne = true; // exit the while
				}
			}
		}
	} else {
		// We're moving down - turn off any that are on in the now-just-above twinkle layer
		CleanupZ = TwinkleLevel + 1;
		if (CleanupZ > 7) {
			// ... This probably can't happen, but...
			return;
		}
		if (Cube.ThisLEDIsOn(CleanupX, CleanupY, CleanupZ)) {
			// Turn this one off and we're done
			Cube.SetLEDColor(CleanupX, CleanupY, CleanupZ, 0, 0, 0);
			GotOne = true;
		} else {
			// This one is already off - look further
			while ((GotOne == false) && NextCleanupPosition()) {
				// Try this new position
				if (Cube.ThisLEDIsOn(CleanupX, CleanupY, CleanupZ)) {
					// Turn it off
					Cube.SetLEDColor(CleanupX, CleanupY, CleanupZ, 0, 0, 0);
					GotOne = true;
				}
			}
		}
	}
}

// Return true if there IS a next position
bool LEDTide::NextCleanupPosition() {
	int AttemptCounter = 10;
	bool FoundOne = false;
	while ((false == FoundOne) && (AttemptCounter > 0)) {
		AttemptCounter--;
		CleanupX = random(0, 8);
		CleanupY = random(0, 8);
		if ((Cube.ThisLEDIsOn(CleanupX, CleanupY, CleanupZ) == false) && (LevelStepDirection == 1)) {
			// This position needs to be turned on
			FoundOne = true;
			return true;
		}
		if ((Cube.ThisLEDIsOn(CleanupX, CleanupY, CleanupZ) == true) && (LevelStepDirection == -1)) {
			// This position needs to be turned off
			FoundOne = true;
			return true;
		}
	}
	// We've exhausted our attempt counter
	return false;
}

void LEDTide::MoveUp() {
	// Cube.FillLayer(TwinkleLevel, LevelColor[TwinkleLevel][0], LevelColor[TwinkleLevel][1], LevelColor[TwinkleLevel][2]);
	SolidLevel++;
	TwinkleLevel++;
	InitializeTwinkleCount();
}

void LEDTide::MoveDown() {
	// Cube.FillLayer(TwinkleLevel, 0, 0, 0);
	SolidLevel--;
	TwinkleLevel--;
	InitializeTwinkleCount();
}

// A change

void LEDTide::StepTide() {
	int X = random(0, 8);
	int Y = random(0, 8);
	switch(random(0, 2)) {
	case 0:
		Cube.SetLEDColor(X, Y, TwinkleLevel, LevelColor[TwinkleLevel][0], LevelColor[TwinkleLevel][1], LevelColor[TwinkleLevel][2]);
		break;
	case 1:
		Cube.SetLEDColor(X, Y, TwinkleLevel, 0, 0, 0);
		break;
	default:
		Serial1.write("Hit default case in LEDTide::StepTide()");
		break;
	}
	TwinkleStepCount--;
	if (TwinkleStepCount < 1) {
		// Move to the next level
		if (LevelStepDirection == 1) {
			// We're going up
			if (TwinkleLevel == 7) {
				// We're at the top
				LevelStepDirection = -1;
				MoveDown();
			} else {
				// We can move up
				MoveUp();
			}
		} else {
			// We're going down
			if (SolidLevel == 0) {
				// We're at the bottom
				StartTide();
			} else {
				// We can move down
				MoveDown();
			}
		}
	}
	CleanupNext();
}
