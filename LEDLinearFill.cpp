// LEDLinearFill.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDLinearFill.h"

extern LEDCube Cube;
extern LEDLinearFill LinearFill;

LEDLinearFill::LEDLinearFill() {

}

int LEDLinearFill::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDLinearFill::StartLinearFill() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(10);
	X = 0;
	Y = 0;
	Z = 0;
	switch(random(0, 8)) {
	case 0:
		Red = 0;
		Green = 0;
		Blue = 0;
		RedGradient = 1;
		GreenGradient = 1;
		BlueGradient = 1;
		break;
	case 1:
		Red = 7;
		Green = 0;
		Blue = 0;
		RedGradient = -1;
		GreenGradient = 1;
		BlueGradient = 1;
		break;
	case 2:
		Red = 0;
		Green = 7;
		Blue = 0;
		RedGradient = 1;
		GreenGradient = -1;
		BlueGradient = 1;
		break;
	case 3:
		Red = 7;
		Green = 7;
		Blue = 0;
		RedGradient = -1;
		GreenGradient = -1;
		BlueGradient = 1;
		break;
	case 4:
		Red = 0;
		Green = 0;
		Blue = 7;
		RedGradient = 1;
		GreenGradient = 1;
		BlueGradient = -1;
		break;
	case 5:
		Red = 7;
		Green = 0;
		Blue = 7;
		RedGradient = -1;
		GreenGradient = 1;
		BlueGradient = -1;
		break;
	case 6:
		Red = 0;
		Green = 7;
		Blue = 7;
		RedGradient = 1;
		GreenGradient = -1;
		BlueGradient = -1;
		break;
	case 7:
		Red = 7;
		Green = 7;
		Blue = 7;
		RedGradient = -1;
		GreenGradient = -1;
		BlueGradient = -1;
		break;
	}
}

void LEDLinearFill::StepLinearFill() {
	Cube.SetLEDColor( X, Y, Z, Red, Green, Blue );
	X++;
	Red += RedGradient;
	if (X > 7){
		X = 0;
		Red -= 8 * RedGradient;
		Y++;
		Green += GreenGradient;
		if (Y > 7) {
			Y = 0;
			Green -= 8 * GreenGradient;
			Z++;
			Blue += BlueGradient;
			if (Z > 7) {
				StartLinearFill();
			}
		}
	}
}

