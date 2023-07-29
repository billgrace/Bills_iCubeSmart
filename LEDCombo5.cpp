// LEDCombo5.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDCombo5.h"
#include "LEDFireworkRocket.h"
#include "LEDSonar.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDCombo5 Combo5;
extern LEDFireworkRocket FireworkRocket;
extern LEDSonar Sonar;

LEDCombo5::LEDCombo5() {

}

int LEDCombo5::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDCombo5::StartCombo5() {
	FireworkRocket.StartFireworkRocket();
	Sonar.StartSonar();
	Cube.SetAnimationDurationInCycles(2);
}

void LEDCombo5::StepCombo5() {
	FireworkRocket.StepFireworkRocket();
	Sonar.StepSonar();
}

