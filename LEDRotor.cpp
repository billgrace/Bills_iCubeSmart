// LEDRotor.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDRotor.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDRotor Rotor;

#define NumberOfModes 4

LEDRotor::LEDRotor() {

}

int LEDRotor::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDRotor::StartRotor() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	TipRed = Cube.RandomColor();
	TipGreen = Cube.RandomColor();
	TipBlue = Cube.RandomColor();
	BarRed = Cube.RandomColor();
	BarGreen = Cube.RandomColor();
	BarBlue = Cube.RandomColor();
	CounterTipRed = Cube.RandomColor();
	CounterTipGreen = Cube.RandomColor();
	CounterTipBlue = Cube.RandomColor();
	CounterBarRed = Cube.RandomColor();
	CounterBarGreen = Cube.RandomColor();
	CounterBarBlue = Cube.RandomColor();
	PrimeAngle = 0;
	ReverseAngle = GetReverseAngle();
	CurrentLevel = 0;
	LevelDelta = 1;
	Mode = random(0, NumberOfModes);
	switch(Mode) {
	case 0:
		// simple all-level rotor
		MinPeriod = 10;
		MaxPeriod = 20;
		StepTarget = random(200, 500);
		break;
	case 1:
		// alternating directions
		MinPeriod = 20;
		MaxPeriod = 30;
		StepTarget = random(200, 500);
		break;
	case 2:
		// rising/falling
		MinPeriod = 10;
		MaxPeriod = 20;
		StepTarget = random(300, 700);
		break;
	case 3:
		// simple all-level running backward
		MinPeriod = 10;
		MaxPeriod = 20;
		StepTarget = random(200, 500);
		break;
	}
	Cube.SetAnimationStepSpeedPeriodTo(random(MinPeriod, MaxPeriod));
}

void LEDRotor::StepRotor() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartRotor();
	}
	switch(Mode) {
	case 0:
		// simple all-level rotor
		for (CurrentLevel = 0; CurrentLevel < 8; CurrentLevel++) {
			DrawRotor(PrimeAngle, CurrentLevel, 0, 0, 0, 0, 0, 0);
		}
		PrimeAngle = Cube.NextIndex(PrimeAngle, RotorMoveAngleCount);
		ReverseAngle = GetReverseAngle();
		for (CurrentLevel = 0; CurrentLevel < 8; CurrentLevel++) {
			DrawRotor(PrimeAngle, CurrentLevel, TipRed, TipGreen, TipBlue, BarRed, BarGreen, BarBlue);
		}
		break;
	case 1:
		// alternating directions
		for (CurrentLevel = 0; CurrentLevel < 8; CurrentLevel++) {
			if ((CurrentLevel % 2) == 0) {
				DrawRotor(PrimeAngle, CurrentLevel, 0, 0, 0, 0, 0, 0);
			} else {
				DrawRotor(ReverseAngle, CurrentLevel, 0, 0, 0, 0, 0, 0);
			}
		}
		PrimeAngle = Cube.NextIndex(PrimeAngle, RotorMoveAngleCount);
		ReverseAngle = GetReverseAngle();
		for (CurrentLevel = 0; CurrentLevel < 8; CurrentLevel++) {
			if ((CurrentLevel % 2) == 0) {
				DrawRotor(PrimeAngle, CurrentLevel, TipRed, TipGreen, TipBlue, BarRed, BarGreen, BarBlue);
			} else {
				DrawRotor(ReverseAngle, CurrentLevel, CounterTipRed, CounterTipGreen, CounterTipBlue, CounterBarRed, CounterBarGreen, CounterBarBlue);
			}
		}
		break;
	case 2:
		// rising/falling
		DrawRotor(PrimeAngle, CurrentLevel, 0, 0, 0, 0, 0, 0);
		PrimeAngle = Cube.NextIndex(PrimeAngle, RotorMoveAngleCount);
		if (PrimeAngle == 0) {
			if (LevelDelta > 0) {
				CurrentLevel++;
				if (CurrentLevel >= 8) {
					LevelDelta = -1;
					CurrentLevel = 6;
				}
			} else {
				CurrentLevel--;
				if (CurrentLevel < 0) {
					LevelDelta = 1;
					CurrentLevel = 1;
				}
			}
		}
		DrawRotor(PrimeAngle, CurrentLevel, TipRed, TipGreen, TipBlue, BarRed, BarGreen, BarBlue);
		break;
	case 3:
		// simple all-level running backward
		for (CurrentLevel = 0; CurrentLevel < 8; CurrentLevel++) {
			DrawRotor(ReverseAngle, CurrentLevel, 0, 0, 0, 0, 0, 0);
		}
		PrimeAngle = Cube.NextIndex(PrimeAngle, RotorMoveAngleCount);
		ReverseAngle = GetReverseAngle();
		for (CurrentLevel = 0; CurrentLevel < 8; CurrentLevel++) {
			DrawRotor(ReverseAngle, CurrentLevel, TipRed, TipGreen, TipBlue, BarRed, BarGreen, BarBlue);
		}
		break;
	}
}

void LEDRotor::DrawRotor(int Angle, int Level, int TipR, int TipG, int TipB, int BarR, int BarG, int BarB) {
	Cube.SetLEDColor(Move.GetRotorMoveX(Angle, 0), Move.GetRotorMoveY(Angle, 0), Level, TipR, TipG, TipB);
	for (int BarPoint = 1; BarPoint < 7; BarPoint++) {
		Cube.SetLEDColor(Move.GetRotorMoveX(Angle, BarPoint), Move.GetRotorMoveY(Angle, BarPoint), Level, BarR, BarG, BarB);
	}
	Cube.SetLEDColor(Move.GetRotorMoveX(Angle, 7), Move.GetRotorMoveY(Angle, 7), Level, TipR, TipG, TipB);
}

int LEDRotor::GetReverseAngle() {
	return RotorMoveAngleCount - 1 - PrimeAngle;
}
