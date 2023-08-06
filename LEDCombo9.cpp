// LEDCombo9.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo9.h"
#include "LEDBinary.h"
#include "LEDShape.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo9 Combo9;
extern LEDBinary Binary;
extern LEDShape Shape;

LEDCombo9::LEDCombo9() {

}

int LEDCombo9::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo9::StartCombo9() {
	Binary.StartBinary();
	Shape.StartShape();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo9::StepCombo9() {
	Binary.StepBinary();
	Shape.StepShape();
}

