// LEDBall.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDBall.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDBall Ball;

LEDBall::LEDBall() {

}

int LEDBall::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDBall::StartBall() {
	AntiMode = random(0, 2);
	BallStyle = random(0, NumberOfBallStyles);
	switch (BallStyle) {
	case 0:
		Cube.SetAnimationStepSpeedPeriodTo(random(40, 150));
		MaxSegmentCount = random(10, 20);
		break;
	case 1:
		Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
		MaxSegmentCount = random(10, 25);
		break;
	case 2:
		Cube.SetAnimationStepSpeedPeriodTo(random(80, 200));
		MaxSegmentCount = random(10, 20);
		break;
	case 3:
		Cube.SetAnimationStepSpeedPeriodTo(random(15, 100));
		MaxSegmentCount = random(20, 35);
		break;
	case 4:
		Cube.SetAnimationStepSpeedPeriodTo(random(50, 100));
		MaxSegmentCount = random(10, 20);
		break;
	default :
		Cube.SetAnimationStepSpeedPeriodTo(random(50, 100));
		MaxSegmentCount = random(5, 10);
		break;
	}
	BallRed = Cube.RandomColor();
	BallGreen = Cube.RandomColor();
	BallBlue = Cube.RandomColor();
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	CurrentSegmentCount = 0;
	Move.InitializeCubeMove(2, 0, 10);
}

void LEDBall::StepBall() {
	// Erase previous
	DrawBalls(Move.GetCurrentCubeMoveX(), Move.GetCurrentCubeMoveY(), Move.GetCurrentCubeMoveZ(), 0, 0, 0);
	// Determine next
	if (Move.AtEndOfCurrentCubeMoveSegment()) {
		CurrentSegmentCount++;
		if (CurrentSegmentCount >= MaxSegmentCount) {
			StartBall();
			return;
		}
		Move.SetupNextCubeMoveSegment();
		Move.StartCubeMoveSegment();
	} else {
		Move.AdvanceToNextCubeMovePosition();
	}
	// Draw next
	DrawBalls(Move.GetCurrentCubeMoveX(), Move.GetCurrentCubeMoveY(), Move.GetCurrentCubeMoveZ(), BallRed, BallGreen, BallBlue);
}

void LEDBall::DrawBalls(int X, int Y, int Z, int Red, int Green, int Blue) {
	int AntiX;
	int AntiY;
	int AntiZ;
	AntiX = 7 - X;
	AntiY = 7 - Y;
	AntiZ = 7 - Z;
	DrawBall(X, Y, Z, Red, Green, Blue);
	if (AntiMode == 1) {
		DrawBall(AntiX, AntiY, AntiZ, Red, Green, Blue);
	}
}

void LEDBall::DrawBall(int X, int Y, int Z, int Red, int Green, int Blue) {
	// Draw center LED
	if ((BallStyle == 0) || (BallStyle == 1) || (BallStyle == 3)) {
		Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
	}

	// Draw inner shell
	if ((BallStyle == 0) || (BallStyle == 1) || (BallStyle == 4)) {
		Cube.SetLEDColor(X + 1, Y, Z, Red, Green, Blue);
		Cube.SetLEDColor(X - 1, Y, Z, Red, Green, Blue);
		Cube.SetLEDColor(X, Y + 1, Z, Red, Green, Blue);
		Cube.SetLEDColor(X, Y - 1, Z, Red, Green, Blue);
		Cube.SetLEDColor(X, Y, Z + 1, Red, Green, Blue);
		Cube.SetLEDColor(X, Y, Z - 1, Red, Green, Blue);
	}

	// Draw outer shell
	if ((BallStyle == 0) || (BallStyle == 2) || (BallStyle == 4)) {
		Cube.SetLEDColor(X, Y + 1, Z + 1, Red, Green, Blue);
		Cube.SetLEDColor(X, Y + 1, Z - 1, Red, Green, Blue);
		Cube.SetLEDColor(X, Y - 1, Z + 1, Red, Green, Blue);
		Cube.SetLEDColor(X, Y - 1, Z - 1, Red, Green, Blue);
		Cube.SetLEDColor(X + 1, Y, Z + 1, Red, Green, Blue);
		Cube.SetLEDColor(X + 1, Y, Z - 1, Red, Green, Blue);
		Cube.SetLEDColor(X - 1, Y, Z + 1, Red, Green, Blue);
		Cube.SetLEDColor(X - 1, Y, Z - 1, Red, Green, Blue);
		Cube.SetLEDColor(X + 1, Y + 1, Z, Red, Green, Blue);
		Cube.SetLEDColor(X + 1, Y - 1, Z, Red, Green, Blue);
		Cube.SetLEDColor(X - 1, Y + 1, Z, Red, Green, Blue);
		Cube.SetLEDColor(X - 1, Y - 1, Z, Red, Green, Blue);
	}
}
