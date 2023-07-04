// LEDShape.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDShape.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDShape Shape;

LEDShape::LEDShape() {

}

int LEDShape::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDShape::StartShape() {
	StepCounter = 0;
	StepTarget = random(100, 200);
	NumberOfShapes = random( 1, 9);
	// Initialize all shapes to "available to start"
	for (int S = 0; S < MaximumNumberOfShapeShapes; S++) {
		Shapes[S][1] = 14;
	}
	SpawnTarget = random(5, 10);
	SpawnCounter = SpawnTarget - 1;
	Cube.ClearImage();
	Cube.SetAnimationStepSpeedPeriodTo(random(60, 100));
	Cube.IncrementAnimationDurationCycleCount();
}

void LEDShape::StepShape() {
	// ? Time to end the animation?
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartShape();
	}
	// ? Time to start a new shape?
	SpawnCounter++;
	if (SpawnCounter >= SpawnTarget) {
		SpawnCounter = 0;
		for (int i = 0; i < NumberOfShapes; i++) {
			if (Shapes[i][1] == 14) {
				// this shape is available to start...
				// start it
				Shapes[i][1] = 0;
				// give it a shape
				Shapes[i][0] = random(0, 11);
				// give it a color
				switch (random(0, 7)) {
				case 0:
					Shapes[i][2] = 0x700;
					break;
				case 1:
					Shapes[i][2] = 0x070;
					break;
				case 2:
					Shapes[i][2] = 0x007;
					break;
				case 3:
					Shapes[i][2] = 0x077;
					break;
				case 4:
					Shapes[i][2] = 0x707;
					break;
				case 5:
					Shapes[i][2] = 0x770;
					break;
				case 6:
					Shapes[i][2] = 0x777;
					break;
				}
				// give it a position
				Shapes[i][3] = random(2, 6);
				Shapes[i][4] = random(2, 6);
				Shapes[i][5] = random(2, 6);
				// Only start one at a time
				break;
			}
		}
	}
	// ? Any active shapes to bump to the next step?
	for (int S = 0; S < NumberOfShapes; S++) {
		if (Shapes[S][1] < 14 ) {
			// this shape is active so bump it to the next step
			NudgeShape(S);
		}
	}
}

void LEDShape::NudgeShape(int Index) {
	int Color = Shapes[Index][2];
	int FullRed = Color >> 8;
	int FullGreen = (Color >> 4) & 0xF;
	int FullBlue = Color & 0xF;
	int X = Shapes[Index][3];
	int Y = Shapes[Index][4];
	int Z = Shapes[Index][5];
	int DimmingFactor;
	switch (Shapes[Index][1]) {
	case 0:
		DimmingFactor = 6;
		break;
	case 1:
		DimmingFactor = 5;
		break;
	case 2:
		DimmingFactor = 4;
		break;
	case 3:
		DimmingFactor = 3;
		break;
	case 4:
		DimmingFactor = 2;
		break;
	case 5:
		DimmingFactor = 1;
		break;
	case 6:
		DimmingFactor = 0;
		break;
	case 7:
		DimmingFactor = 1;
		break;
	case 8:
		DimmingFactor = 2;
		break;
	case 9:
		DimmingFactor = 3;
		break;
	case 10:
		DimmingFactor = 4;
		break;
	case 11:
		DimmingFactor = 5;
		break;
	case 12:
		DimmingFactor = 6;
		break;
	case 13:
		DimmingFactor = 7;
		break;
	case 14:
		break;
	}
	Shapes[Index][1]++;
	DrawShape(Shapes[Index][0], FullRed - DimmingFactor, FullGreen - DimmingFactor, FullBlue - DimmingFactor, X, Y, Z);
}

void LEDShape::DrawShape(int ShapeType, int R, int G, int B, int X, int Y, int Z) {
	switch (ShapeType) {
	case 0:
		// Single LED
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		break;
	case 1:
		// 2x2 cube
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z+1, R, G, B);
		break;
	case 2:
		// radius 1 solid sphere
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y, Z-1, R, G, B);
		break;
	case 3:
		// radius 1 hollow sphere
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y, Z-1, R, G, B);
		break;
	case 4:
		// 3x3 cube
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y, Z-1, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z-1, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z-1, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z-1, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z-1, R, G, B);
		Cube.SetLEDColor(X+1, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y-1, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y-1, Z-1, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z-1, R, G, B);
		Cube.SetLEDColor(X-1, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y+1, Z+1, R, G, B);
		Cube.SetLEDColor(X-1, Y+1, Z-1, R, G, B);
		Cube.SetLEDColor(X-1, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y-1, Z+1, R, G, B);
		Cube.SetLEDColor(X-1, Y-1, Z-1, R, G, B);
		break;
	case 5:
		// 2x2 X-normal square
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z+1, R, G, B);
		break;
	case 6:
		// 2x2 Y-normal square
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z+1, R, G, B);
		break;
	case 7:
		// 2x2 Z-normal square
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z, R, G, B);
		break;
	case 8:
		// 3x3 X-normal square
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y, Z-1, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z-1, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z-1, R, G, B);
		break;
	case 9:
		// 3x3 Y-normal square
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X, Y, Z-1, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z-1, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z+1, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z-1, R, G, B);
		break;
	case 10:
		// 3x3 Z-normal square
		Cube.SetLEDColor(X, Y, Z, R, G, B);
		Cube.SetLEDColor(X, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X+1, Y-1, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y+1, Z, R, G, B);
		Cube.SetLEDColor(X-1, Y-1, Z, R, G, B);
		break;
	}
}