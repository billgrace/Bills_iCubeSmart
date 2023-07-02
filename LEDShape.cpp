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
	Cube.IncrementAnimationDurationCycleCount();
}

void LEDShape::StepShape() {
	StepShape();
}

