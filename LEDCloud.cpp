// LEDCloud.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCloud.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCloud Cloud;

LEDCloud::LEDCloud() {

}

int LEDCloud::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCloud::StartCloud() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	StepCounter = 0;
	StepTarget = random(200, 500);
	StartNewCounter = 0;
	StartNewTarget = random(3, 6);
	// Set all the clouds in the data array to "available"
	for (int i = 0; i < LEDCloudMaxNumberOfClouds; i++) {
		Cloud[i][8] = 0;
	}
	StartANewCloud();
}

void LEDCloud::StepCloud() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartCloud();
	}
	StartNewCounter++;
	if (StartNewCounter >= StartNewTarget) {
		StartNewCounter = 0;
		StartANewCloud();
	}
	for (int i = 0; i < LEDCloudMaxNumberOfClouds; i++) {
		if (Cloud[i][8] != 0) {
			DrawCloud(i);
		}
	}
}

void LEDCloud::StartANewCloud() {
	int CompositeColor;
	int EdgeLength;
	// First find an available spot in the data array
	for (int i = 0; i < LEDCloudMaxNumberOfClouds; i++) {
		if (Cloud[i][8] == 0) {
			// This cloud is available
			// Mark it as "getting brighter from dimmest possible"
			Cloud[i][8] = 1;
			Cloud[i][7] = 1;
			// Get a random primary color
			CompositeColor = Cube.RandomSolidColor();
			Cloud[i][0] = Cube.RedPartOf(CompositeColor);
			Cloud[i][1] = Cube.GreenPartOf(CompositeColor);
			Cloud[i][2] = Cube.BluePartOf(CompositeColor);
			// Figure the size and location
			EdgeLength = random(2, 5);
			Cloud[i][3] = EdgeLength;
			Cloud[i][4] = random(0, (9 - EdgeLength));
			Cloud[i][5] = random(0, (9 - EdgeLength));
			Cloud[i][6] = random(0, (9 - EdgeLength));
			// Exit the for loop so we only start *ONE* cloud
			break;
		}
	}
}

void LEDCloud::DrawCloud(int Index) {
	int Red;
	int Green;
	int Blue;
	int Brightness;
	int DimmingFactor;
	int BrightnessDelta;
	int X1;
	int X2;
	int Y1;
	int Y2;
	int Z1;
	int Z2;
	int EdgeLength;
	// Figure the coordinates to draw
	EdgeLength = Cloud[Index][3];
	X1 = Cloud[Index][4];
	X2 = X1 + EdgeLength;
	Y1 = Cloud[Index][5];
	Y2 = Y1 + EdgeLength;
	Z1 = Cloud[Index][6];
	Z2 = Z1 + EdgeLength;
	// Figure the color to draw
	// ... first get the primary color values (0 or 7)
	Red = Cloud[Index][0];
	Green = Cloud[Index][1];
	Blue = Cloud[Index][2];
	// ... now adjust those primary values to the present brightness
	Brightness = Cloud[Index][7];
	DimmingFactor = 7 - Brightness;
	BrightnessDelta = Cloud[Index][8];
	if (Red == 7) {
		Red = Red - DimmingFactor;
	}
	if (Green == 7) {
		Green = Green - DimmingFactor;
	}
	if (Blue == 7) {
		Blue = Blue - DimmingFactor;
	}
	// Adjust the brightness to be used next time around
	if (BrightnessDelta == -1) {
		// This cloud is getting dimmer
		if (Brightness == 1) {
			// This cloud is at its last brightness so just turn it off
			Cloud [Index][8] = 0;
			Red = 0;
			Green = 0;
			Blue = 0;
		} else {
			// This cloud has further dimming ahead of it yet
			Cloud[Index][7]--;
		}
	} else {
		// This cloud is getting brighter
		if (Brightness == 7) {
			// This cloud is fully bright so turn it around to getting dimmer next time
			Cloud [Index][8] = -1;
		} else {
			// This cloud has further brightening ahead of it yet
			Cloud[Index][7]++;
		}
	}
	// And finally draw the cloud
	for (int X = X1; X < X2; X++) {
		for (int Y = Y1; Y < Y2; Y++) {
			for (int Z = Z1; Z < Z2; Z++) {
				Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			}
		}
	}
}

