// LEDFireworkRocket.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDFireworkRocket.h"

extern LEDCube Cube;
extern LEDFireworkRocket FireworkRocket;

LEDFireworkRocket::LEDFireworkRocket() {

}

int LEDFireworkRocket::SuggestedNumberOfAnimationCycles() {
	return random(2, 4);
}

void LEDFireworkRocket::StartFireworkRocket() {
	// Register the start of a new animation cycle
	Cube.IncrementAnimationDurationCycleCount();
  
	Cube.ClearImage();

	SegmentNumber = 0;
	ArcSpeed = random(30, 150);
	FireballSpeed = random(30, 150);
	ShimmerSpeed = random(30, 150);
	ShimmerCounter = random(5, 10);
	StartArc();
}

void LEDFireworkRocket::StepFireworkRocket() {
	switch(SegmentNumber) {
	case 0:
		// Arc
		switch(ArcStageNumber) {
		case 0:
			// Rising (point numbers 1 through 6)
			Cube.SetLEDColor( ArcX, ArcY, ArcZ, ArcRed, ArcGreen, ArcBlue );
			ArcPointNumber++;
			if (ArcPointNumber == 7) {
				// Just did top point in straight vertical arc
				ArcX += ArcDeltaX;
				ArcY += ArcDeltaY;
				ArcZ = 6;
				ArcStageNumber = 1;
			} else {
				// Just did another point in the straight vertical rise
				ArcZ++;
			}
			break;
		case 1:
			// Curving (point numbers 7 through 9)
			Cube.SetLEDColor( ArcX, ArcY, ArcZ, ArcRed, ArcGreen, ArcBlue );
			ArcPointNumber++;
			ArcX += ArcDeltaX;
			ArcY += ArcDeltaY;
			switch(ArcPointNumber) {
			case 8:
				ArcZ = 7;
				break;
			case 9:
				ArcZ = 6;
				break;
			case 10:
				ArcZ = 5;
				ArcX -= ArcDeltaX;
				ArcY -= ArcDeltaY;
				ArcStageNumber++;
				break;
			}
			break;
		case 2:
			// Falling (point numbers 10 & 11)
			Cube.SetLEDColor( ArcX, ArcY, ArcZ, ArcRed, ArcGreen, ArcBlue );
			ArcPointNumber++;
			ArcZ--;
			if (ArcPointNumber == 12) {
				StartFireball();
			}
			break;
		}
		break;
	case 1:
		// Fireball
		switch(FireballStageNumber) {
		case 0:
			// Fireball center
			FireballStageNumber++;
			FireballCenter(ArcX, ArcY, ArcZ, FireballCenterRed, FireballCenterGreen, FireballCenterBlue);
			break;
		case 1:
			// Fireball shell1
			FireballStageNumber++;
			FireballShell1(ArcX, ArcY, ArcZ, FireballShell1Red, FireballShell1Green, FireballShell1Blue);
			break;
		case 2:
			// Fireball shell2
			FireballStageNumber++;
			FireballShell2(ArcX, ArcY, ArcZ, FireballShell2Red, FireballShell2Green, FireballShell2Blue);
			break;
		case 3:
			// Fireball shell3
			FireballShell3(ArcX, ArcY, ArcZ, FireballShell3Red, FireballShell3Green, FireballShell3Blue);
			StartShimmering();
			break;
		}
		break;
	case 2:
		// Shimmer
		FireballShell3Red = FireballShell2Red;
		FireballShell3Green = FireballShell2Green;
		FireballShell3Blue = FireballShell2Blue;
		FireballShell2Red = FireballShell1Red;
		FireballShell2Green = FireballShell1Green;
		FireballShell2Blue = FireballShell1Blue;
		FireballShell1Red = FireballCenterRed;
		FireballShell1Green = FireballCenterGreen;
		FireballShell1Blue = FireballCenterBlue;
		FireballCenterRed = Cube.RandomColor();
		FireballCenterGreen = Cube.RandomColor();
		FireballCenterBlue = Cube.RandomColor();
		FireballCenter(ArcX, ArcY, ArcZ, FireballCenterRed, FireballCenterGreen, FireballCenterBlue);
		FireballShell1(ArcX, ArcY, ArcZ, FireballShell1Red, FireballShell1Green, FireballShell1Blue);
		FireballShell2(ArcX, ArcY, ArcZ, FireballShell2Red, FireballShell2Green, FireballShell2Blue);
		FireballShell3(ArcX, ArcY, ArcZ, FireballShell3Red, FireballShell3Green, FireballShell3Blue);
		ShimmerCounter--;
		if (ShimmerCounter < 1) {
			StartFireworkRocket();
		}
		break;
	}
}

void LEDFireworkRocket::FireballCenter(int X, int Y, int Z, int Red, int Green, int Blue) {
	Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
}

void LEDFireworkRocket::FireballShell1(int X, int Y, int Z, int Red, int Green, int Blue) {
	Cube.SetLEDColor(X+1, Y, Z, Red, Green, Blue);
	Cube.SetLEDColor(X-1, Y, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y+1, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y-1, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y, Z+1, Red, Green, Blue);
	Cube.SetLEDColor(X, Y, Z-1, Red, Green, Blue);
}

void LEDFireworkRocket::FireballShell2(int X, int Y, int Z, int Red, int Green, int Blue) {
  Cube.SetLEDColor(X+1, Y+1, Z, Red, Green, Blue);
  Cube.SetLEDColor(X-1, Y-1, Z, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X-1, Y, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y+1, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y-1, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y-1, Z, Red, Green, Blue);
  Cube.SetLEDColor(X-1, Y+1, Z, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X-1, Y, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y+1, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y-1, Z+1, Red, Green, Blue);
}

void LEDFireworkRocket::FireballShell3(int X, int Y, int Z, int Red, int Green, int Blue) {
  Cube.SetLEDColor(X+2, Y, Z, Red, Green, Blue);
  Cube.SetLEDColor(X-2, Y, Z, Red, Green, Blue);
  Cube.SetLEDColor(X, Y+2, Z, Red, Green, Blue);
  Cube.SetLEDColor(X, Y-2, Z, Red, Green, Blue);
  Cube.SetLEDColor(X, Y, Z+2, Red, Green, Blue);
  Cube.SetLEDColor(X, Y, Z-2, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y+1, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y+1, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y-1, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X+1, Y-1, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y+1, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y+1, Z-1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y-1, Z+1, Red, Green, Blue);
  Cube.SetLEDColor(X, Y-1, Z-1, Red, Green, Blue);
}

void LEDFireworkRocket::StartArc() {
	ArcStageNumber = 0;
	ArcPointNumber = 1;
    Cube.SetAnimationStepSpeedPeriodTo(ArcSpeed);
    ArcRed = Cube.RandomColor();
    ArcGreen = Cube.RandomColor();
    ArcBlue = Cube.RandomColor();
    // Always start at ground level
    ArcZ = 0;
    ArcDeltaZ = 1;
    // Pick one of four corners
    switch(random(0, 4)) {
    case 0:
    	ArcX = 0;
    	ArcY = 0;
    	ArcDeltaX = 1;
    	ArcDeltaY = 1;
    	break;
    case 1:
    	ArcX = 7;
    	ArcY = 0;
    	ArcDeltaX = -1;
    	ArcDeltaY = 1;
    	break;
    case 2:
    	ArcX = 0;
    	ArcY = 7;
    	ArcDeltaX = 1;
    	ArcDeltaY = -1;
    	break;
    case 3:
    	ArcX = 7;
    	ArcY = 7;
    	ArcDeltaX = -1;
    	ArcDeltaY = -1;
    	break;
    }
}

void LEDFireworkRocket::StartFireball() {
	SegmentNumber = 1;
	FireballStageNumber = 0;
	Cube.SetAnimationStepSpeedPeriodTo(FireballSpeed);
	FireballCenterRed = Cube.RandomColor();
	FireballCenterGreen = Cube.RandomColor();
	FireballCenterBlue = Cube.RandomColor();
	FireballShell1Red = Cube.RandomColor();
	FireballShell1Green = Cube.RandomColor();
	FireballShell1Blue = Cube.RandomColor();
	FireballShell2Red = Cube.RandomColor();
	FireballShell2Green = Cube.RandomColor();
	FireballShell2Blue = Cube.RandomColor();
	FireballShell3Red = Cube.RandomColor();
	FireballShell3Green = Cube.RandomColor();
	FireballShell3Blue = Cube.RandomColor();
}

void LEDFireworkRocket::StartShimmering() {
	SegmentNumber = 2;
	Cube.SetAnimationStepSpeedPeriodTo(ShimmerSpeed);
}
