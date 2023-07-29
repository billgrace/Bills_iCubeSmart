// LEDBasketBall.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDBasketBall.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDBasketBall BasketBall;

LEDBasketBall::LEDBasketBall() {

}

int LEDBasketBall::SuggestedNumberOfAnimationCycles() {
	return random(5, 8);
}

void LEDBasketBall::StartBasketBall() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	Stage = 1;
	BallRed = Cube.RandomColor();
	BallGreen = Cube.RandomColor();
	BallBlue = Cube.RandomColor();
	HoopRed = Cube.RandomColor();
	HoopGreen = Cube.RandomColor();
	HoopBlue = Cube.RandomColor();
	// Pick a hoop location
	switch (random(0, 8)) {
	case 0:
		// Front left corner
		HoopX = random(1, 3);
		HoopY = random(1, 3);
		break;
	case 1:
		// Front side
		HoopX = random(3, 5);
		HoopY = random(1, 3);
		break;
	case 2:
		// Front right corner
		HoopX = random(4, 6);
		HoopY = random(1, 3);
		break;
	case 3:
		// Right side
		HoopX = random(4, 6);
		HoopY = random(3, 5);
		break;
	case 4:
		// Rear right corner
		HoopX = random(4, 6);
		HoopY = random(4, 6);
		break;
	case 5:
		// Rear side
		HoopX = random(3, 5);
		HoopY = random(4, 6);
		break;
	case 6:
		// Rear left corner
		HoopX = random(1, 3);
		HoopY = random(4, 6);
		break;
	case 7:
		// Left side
		HoopX = random(1, 3);
		HoopY = random(3, 5);
		break;
	}
	// Pick a hoop height
	HoopZ = random(4, 6);
	// Draw the hoop
	Cube.SetLEDColor(HoopX+1, HoopY+1, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX+1, HoopY, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX+1, HoopY-1, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX, HoopY+1, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX, HoopY-1, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX-1, HoopY+1, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX-1, HoopY, HoopZ, HoopRed, HoopGreen, HoopBlue);
	Cube.SetLEDColor(HoopX-1, HoopY-1, HoopZ, HoopRed, HoopGreen, HoopBlue);
	// Take ball start location from hoop location
	BallX = 7 - HoopX;
	BallY = 7 - HoopY;
	// Figure out which way the ball must move horizontally to get to the hoop
	if (HoopX == BallX) {
		// Both X coordinates are the same
		Stage2DeltaX = 0;
	} else if (HoopX > BallX) {
		// Ball needs to move +X
		Stage2DeltaX = 1;
	} else {
		// Ball needs to move -X
		Stage2DeltaX = -1;
	}
	if (HoopY == BallY) {
		// Both Y coordinates are the same
		Stage2DeltaY = 0;
	} else if (HoopY > BallY) {
		// Ball needs to move +Y
		Stage2DeltaY = 1;
	} else {
		// Ball needs to move -Y
		Stage2DeltaY = -1;
	}
	// Keep the vertical motion simple
	BallZ = HoopZ;
	Stage2Z = BallZ + 2;
	// Draw the ball in it's starting position
	Cube.SetLEDColor(BallX, BallY, BallZ, BallRed, BallGreen, BallBlue);
}

void LEDBasketBall::StepBasketBall() {
	// First erase ball present position
	Cube.SetLEDColor(BallX, BallY, BallZ, 0, 0, 0);
	// Then move the ball position
	switch (Stage) {
	case 1:
		// Rise from shooter
		if (BallZ >= Stage2Z) {
			Stage = 2;
			BallX += Stage2DeltaX;
			BallY += Stage2DeltaY;
		} else {
			BallZ++;
		}
		break;
	case 2:
		// Move horizontally from shooter to hoop
		if (BallX != HoopX) {
			BallX += Stage2DeltaX;
		}
		if (BallY != HoopY) {
			BallY += Stage2DeltaY;
		}
		// Are we there yet?
		if ((BallX == HoopX) && (BallY == HoopY)) {
			Stage = 3;
		}
		break;
	case 3:
		// Fall through hoop
		if (BallZ <= (HoopZ - 2)) {
			StartBasketBall();
		} else {
			BallZ--;
		}
		break;
	}
	// Finally draw the ball in its new position
	Cube.SetLEDColor(BallX, BallY, BallZ, BallRed, BallGreen, BallBlue);
}
