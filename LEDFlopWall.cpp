// LEDFlopWall.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDFLopWall.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDFlopWall FlopWall;

LEDFlopWall::LEDFlopWall() {

}

int LEDFlopWall::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDFlopWall::StartFlopWall() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 100));
	Move.InitializeHingeMove();
	NumberOfFlops = random(10, 15);
	FlopCount = 0;
	Angle = 0;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	CurrentPattern = random(0, NumberOfFlopWallPatterns);
}

void LEDFlopWall::StepFlopWall() {
	if (Angle > 0) {
		Angle--;
		DrawWall(0, 0, 0);
		Angle++;
	}
	DrawWall(Red, Green, Blue);
	Angle++;
	if (Angle > 6) {
		FlopCount++;
		if (FlopCount >= NumberOfFlops) {
			StartFlopWall();
		} else {
			Angle = 0;
			Move.SetupNextHingeFace();
		}
	}
}

void LEDFlopWall::DrawWall(int R, int B, int G) {
	int X;
	int Y;
	int Z;
	int Position;
	switch (Move.GetCurrentSwivel()) {
	case 0:
		for (Z = 0; Z < 8; Z++) {
			for (Position = 0; Position < 8; Position++) {
				X = Move.GetHingePosition0(Angle, Position);
				Y = Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 1:
		for (Y = 7; Y >= 0; Y--) {
			for (Position = 0; Position < 8; Position++) {
				X = Move.GetHingePosition0(Angle, Position);
				Z = Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 2:
		for (Z = 7; Z >= 0; Z--) {
			for (Position = 0; Position < 8; Position++) {
				Y = 7 - Move.GetHingePosition1(Angle, Position);
				X = Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 3:
		for (Y = 0; Y < 8; Y++) {
			for (Position = 0; Position < 8; Position++) {
				Z = 7 - Move.GetHingePosition1(Angle, Position);
				X = Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 4:
		for (Z = 7; Z >= 0; Z--) {
			for (Position = 0; Position < 8; Position++) {
				Y = Move.GetHingePosition0(Angle, Position);
				X = Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 5:
		for (X = 0; X < 8; X++) {
			for (Position = 0; Position < 8; Position++) {
				Y = Move.GetHingePosition0(Angle, Position);
				Z = Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 6:
		for (Z = 0; Z < 8; Z++) {
			for (Position = 0; Position < 8; Position++) {
				X = 7 - Move.GetHingePosition1(Angle, Position);
				Y = Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 7:
		for (X = 7; X >= 0; X--) {
			for (Position = 0; Position < 8; Position++) {
				Z = 7 - Move.GetHingePosition1(Angle, Position);
				Y = Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 8:
		for (Y = 0; Y < 8 ; Y++) {
			for (Position = 0; Position < 8; Position++) {
				Z = Move.GetHingePosition0(Angle, Position);
				X = Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 9:
		for (X = 7; X >= 0; X--) {
			for (Position = 0; Position < 8; Position++) {
				Z = Move.GetHingePosition0(Angle, Position);
				Y = Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 10:
		for (Y = 7; Y >= 0; Y--) {
			for (Position = 0; Position < 8; Position++) {
				X = 7 - Move.GetHingePosition1(Angle, Position);
				Z = Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 11:
		for (X = 0; X < 8; X++) {
			for (Position = 0; Position < 8; Position++) {
				Y = 7 - Move.GetHingePosition1(Angle, Position);
				Z = Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 12:
		for (Z = 7; Z >= 0; Z--) {
			for (Position = 0; Position < 8; Position++) {
				Y = Move.GetHingePosition1(Angle, Position);
				X = 7 - Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 13:
		for (Y = 0; Y < 8; Y++) {
			for (Position = 0; Position < 8; Position++) {
				Z = Move.GetHingePosition1(Angle, Position);
				X = 7 - Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 14:
		for (Z = 0; Z < 8; Z++) {
			for (Position = 0; Position < 8; Position++) {
				X = 7 - Move.GetHingePosition0(Angle, Position);
				Y = 7 - Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 15:
		for ( Y = 7; Y >= 0; Y--) {
			for (Position = 0; Position < 8; Position++) {
				X = 7 - Move.GetHingePosition0(Angle, Position);
				Z = 7 - Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 16:
		for ( Z = 0; Z < 8; Z++) {
			for (Position = 0; Position < 8; Position++) {
				X = Move.GetHingePosition1(Angle, Position);
				Y = 7 - Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 17:
		for ( X = 7; X >= 0; X--) {
			for (Position = 0; Position < 8; Position++) {
				Z = Move.GetHingePosition1(Angle, Position);
				Y = 7 - Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 18:
		for ( Z = 7; Z >= 0; Z--) {
			for (Position = 0; Position < 8; Position++) {
				Y = 7 - Move.GetHingePosition0(Angle, Position);
				X = 7 - Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Z][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 19:
		for ( X = 0; X < 8; X++) {
			for (Position = 0; Position < 8; Position++) {
				Y = 7 - Move.GetHingePosition0(Angle, Position);
				Z = 7 - Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 20:
		for ( Y = 7; Y >= 0; Y--) {
			for (Position = 0; Position < 8; Position++) {
				X = Move.GetHingePosition1(Angle, Position);
				Z = 7 - Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 21:
		for ( X = 0; X < 8; X++) {
			for (Position = 0; Position < 8; Position++) {
				Y = Move.GetHingePosition1(Angle, Position);
				Z = 7 - Move.GetHingePosition0(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 22:
		for ( Y = 0; Y < 8; Y++) {
			for (Position = 0; Position < 8; Position++) {
				Z = 7 - Move.GetHingePosition0(Angle, Position);
				X = 7 - Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][Y][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	case 23:
		for ( X = 7; X >= 0; X--) {
			for (Position = 0; Position < 8; Position++) {
				Z = 7 - Move.GetHingePosition0(Angle, Position);
				Y = 7 - Move.GetHingePosition1(Angle, Position);
				if (Patterns[CurrentPattern][X][Position] == 1)
					Cube.SetLEDColor(X, Y, Z, R, G, B);
			}
		}
		break;
	}
}