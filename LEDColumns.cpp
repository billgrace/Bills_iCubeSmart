// LEDColumns.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDColumns.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDColumns Columns;

LEDColumns::LEDColumns () {

}

int LEDColumns::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDColumns::StartColumns() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	ColumnCounter = 0;
	ColumnTarget = random(70, 115);
	Mode = random(0, 3);
	StartAColumn();
}

void LEDColumns::StepColumns() {
	if (Length == 8) {
		StartAColumn();
	} else {
		switch (Direction) {
		case 0:
			// Grow in X+ direction
			X = Length;
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, Z+1, Red, Green, Blue);
			Cube.SetLEDColor(X, Y+1, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y+1, Z+1, Red, Green, Blue);
			break;
		case 1:
			// Grow in X- direction
			X = 7 - Length;
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, Z+1, Red, Green, Blue);
			Cube.SetLEDColor(X, Y+1, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y+1, Z+1, Red, Green, Blue);
			break;
		case 2:
			// Grow in Y+ direction
			Y = Length;
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, Z+1, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y, Z+1, Red, Green, Blue);
			break;
		case 3:
			// Grow in Y- direction
			Y = 7 - Length;
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y, Z+1, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y, Z+1, Red, Green, Blue);
			break;
		case 4:
			// Grow in Z+ direction
			Z = Length;
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y+1, Z, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y+1, Z, Red, Green, Blue);
			break;
		case 5:
			// Grow in Z- direction
			Z = 7 - Length;
			Cube.SetLEDColor(X, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X, Y+1, Z, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y, Z, Red, Green, Blue);
			Cube.SetLEDColor(X+1, Y+1, Z, Red, Green, Blue);
			break;
		}
		Length++;
	}
}

void LEDColumns::StartAColumn() {
	ColumnCounter++;
	if (ColumnCounter >= ColumnTarget) {
		StartColumns();
	} else {
		Direction = random(0, 6);
		Length = 0;
		switch(Mode) {
		case 0:
			// always light up more columns
			Red = Cube.RandomColor();
			Green = Cube.RandomColor();
			Blue = Cube.RandomColor();
			break;
		case 1:
			// alternate between lighting up and erasing columns
			if ((ColumnCounter % 2) == 1) {
				// erase
				Red = 0;
				Green = 0;
				Blue = 0;
			} else {
				// light up
				Red = Cube.RandomColor();
				Green = Cube.RandomColor();
				Blue = Cube.RandomColor();
			}
			break;
		case 2:
			// light up columns until animation is half done then erase them
			if (ColumnCounter > (ColumnTarget / 2)) {
				// erase
				Red = 0;
				Green = 0;
				Blue = 0;
			} else {
				// light up
				Red = Cube.RandomColor();
				Green = Cube.RandomColor();
				Blue = Cube.RandomColor();
			}
			break;
		}
		switch (Direction) {
		case 0:
			// Grow in X+ direction
			Y = Cube.RandomPickOfFour(0, 2, 4, 6);
			Z = Cube.RandomPickOfFour(0, 2, 4, 6);
			break;
		case 1:
			// Grow in X- direction
			Y = Cube.RandomPickOfFour(0, 2, 4, 6);
			Z = Cube.RandomPickOfFour(0, 2, 4, 6);
			break;
		case 2:
			// Grow in Y+ direction
			X = Cube.RandomPickOfFour(0, 2, 4, 6);
			Z = Cube.RandomPickOfFour(0, 2, 4, 6);
			break;
		case 3:
			// Grow in Y- direction
			X = Cube.RandomPickOfFour(0, 2, 4, 6);
			Z = Cube.RandomPickOfFour(0, 2, 4, 6);
			break;
		case 4:
			// Grow in Z+ direction
			X = Cube.RandomPickOfFour(0, 2, 4, 6);
			Y = Cube.RandomPickOfFour(0, 2, 4, 6);
			break;
		case 5:
			// Grow in Z- direction
			X = Cube.RandomPickOfFour(0, 2, 4, 6);
			Y = Cube.RandomPickOfFour(0, 2, 4, 6);
			break;
		}
	}
}
