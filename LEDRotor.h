// LEDRotor.h
#ifndef LEDRotor_h
#define LEDRotor_h
#include <Arduino.h>

/*
Modes:
0: simple rotor all levels together
1: each level alternates direction of rotation
2: single level rising and falling with each rotation
3: simple rotor all levels rotating backward
*/

class LEDRotor {
private:
	int MinPeriod;
	int MaxPeriod;
	int StepCounter;
	int StepTarget;
	int PrimeAngle;
	int ReverseAngle;
	int CurrentLevel;
	int LevelDelta;
	int Mode;
	int TipRed;
	int TipGreen;
	int TipBlue;
	int BarRed;
	int BarGreen;
	int BarBlue;
	int CounterTipRed;
	int CounterTipGreen;
	int CounterTipBlue;
	int CounterBarRed;
	int CounterBarGreen;
	int CounterBarBlue;
public:
	LEDRotor();
	int SuggestedNumberOfAnimationCycles();
	void StartRotor();
	void StepRotor();
	void DrawRotor(int Angle, int Level, int TipRed, int TipGreen, int TipBlue, int BarRed, int BarGreen, int BarBlue);
	int GetReverseAngle();
};
#endif
