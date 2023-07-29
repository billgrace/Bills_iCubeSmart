// LEDCombo3.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo3.h"
#include "LEDPointToLine.h"
#include "LEDPong.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo3 Combo3;
extern LEDPointToLine PointToLine;
extern LEDPong Pong;

LEDCombo3::LEDCombo3() {

}

int LEDCombo3::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo3::StartCombo3() {
	Pong.StartPong();
	PointToLine.StartPointToLine();
}

void LEDCombo3::StepCombo3() {
	PointToLine.StepPointToLine();
	Pong.StepPong();
}

