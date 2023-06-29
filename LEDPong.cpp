// LEDPong.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDPong.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDPong Pong;

LEDPong::LEDPong() {

}

int LEDPong::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDPong::StartPong() {
	PongShape = random(0, NumberOfPongShapes);
	switch(PongShape) {
	case 0:
		PongRadius = 1;
		break;
	case 1:
		PongRadius = 2;
		break;
	case 2:
		PongRadius = 2;
		break;
	case 3:
		PongRadius = 3;
		break;
	case 4:
		PongRadius = 3;
		break;
	case 5:
		PongRadius = 2;
		break;
	case 6:
		PongRadius = 2;
		break;
	case 7:
		PongRadius = 3;
		break;
	case 8:
		PongRadius = 3;
		break;
	}
	PongStepCounter = 0;
	PongStepLength = random(MaximumNumberOfPongSteps/2, MaximumNumberOfPongSteps);
	LapStepCounter = 0;
	LapStepTarget = PongStepLength/random(3, 8);
	PongRed = Cube.RandomColor();
	PongGreen = Cube.RandomColor();
	PongBlue = Cube.RandomColor();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Move.InitializePongMove(PongRadius);
}

void LEDPong::StepPong() {
	PongStepCounter++;
	if (PongStepCounter > PongStepLength) {
		StartPong();
		return;
	}
	// Erase previous
	DrawPong(Move.GetCurrentPongMoveX(), Move.GetCurrentPongMoveY(), Move.GetCurrentPongMoveZ(), 0, 0, 0);
	LapStepCounter++;
	if (LapStepCounter > LapStepTarget) {
		LapStepCounter = 0;
		Move.InitializePongMove(PongRadius);
		PongRed = Cube.RandomColor();
		PongGreen = Cube.RandomColor();
		PongBlue = Cube.RandomColor();
	}
	// Determine next
	Move.StepPongMove();
	// Draw next
	DrawPong(Move.GetCurrentPongMoveX(), Move.GetCurrentPongMoveY(), Move.GetCurrentPongMoveZ(), PongRed, PongGreen, PongBlue);
}

void LEDPong::DrawPong(int X, int Y, int Z, int Red, int Green, int Blue) {
	int i;
	int j;
	int k;
	switch(PongShape) {
	case 0:
		// center LED only
		Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		break;
	case 1:
		// 3 x 3 solid cube
		for (i = X-1; i < X+2; i++) {
			for (j = Y-1; j < Y+2; j++) {
				for (k = Z-1; k < Z+2; k++) {
					Cube.SetLEDColor(i, j, k, Red, Green, Blue);
				}
			}
		}
		break;
	case 2:
		// 3 x 3 solid ball
		Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		DrawPongBall2(X, Y, Z, Red, Green, Blue);
		break;
	case 3:
		// 5 x 5 solid cube
		for (i = X-2; i < X+3; i++) {
			for (j = Y-2; j < Y+3; j++) {
				for (k = Z-2; k < Z+3; k++) {
					Cube.SetLEDColor(i, j, k, Red, Green, Blue);
				}
			}
		}
		break;
	case 4:
		// 5 x 5 solid ball
		Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
		DrawPongBall2(X, Y, Z, Red, Green, Blue);
		DrawPongBall3(X, Y, Z, Red, Green, Blue);
		break;
	case 5:
		// 3 x 3 hollow cube
		for (i = X-1; i < X+2; i++) {
			for (j = Y-1; j < Y+2; j++) {
				for (k = Z-1; k < Z+2; k++) {
					if ((i != X) || (j != Y) || (k != Z)) {
						Cube.SetLEDColor(i, j, k, Red, Green, Blue);
					}
				}
			}
		}
		break;
	case 6:
		// 3 x 3 hollow ball
		DrawPongBall2(X, Y, Z, Red, Green, Blue);
		break;
	case 7:
		// 5 x 5 hollow cube
		for (i = X-2; i < X+3; i++) {
			for (j = Y-2; j < Y+3; j++) {
				for (k = Z-2; k < Z+3; k++) {
					if ((i == (X-2)) || (i == (X+2)) || (j == (Y-2)) || (j == (Y+2)) || (k == (Z-2)) || (k == (Z+2))) {
						Cube.SetLEDColor(i, j, k, Red, Green, Blue);
					}
				}
			}
		}
		break;
	case 8:
		// 5 x 5 hollow ball
		DrawPongBall3(X, Y, Z, Red, Green, Blue);
		break;
	}
}

void LEDPong::DrawPongBall2(int X, int Y, int Z, int Red, int Green, int Blue) {
	Cube.SetLEDColor(X + 1, Y, Z, Red, Green, Blue);
	Cube.SetLEDColor(X - 1, Y, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y + 1, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y - 1, Z, Red, Green, Blue);
	Cube.SetLEDColor(X, Y, Z + 1, Red, Green, Blue);
	Cube.SetLEDColor(X, Y, Z - 1, Red, Green, Blue);
}

void LEDPong::DrawPongBall3(int X, int Y, int Z, int Red, int Green, int Blue) {
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
