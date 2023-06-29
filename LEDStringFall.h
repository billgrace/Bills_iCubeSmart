// LEDStringFall.h
#ifndef StringFall_h
#define StringFall_h
#include <Arduino.h>

/*
Stages:
0: Filling in the top level
1: Falling from the top level to the bottom level
2: Emptying the bottom layer
ElementColor array:
[X position][Y position][Z Position / Red / Green / Blue]
*/
class LEDStringFall {
private:
	int CurrentStage;
	int ElementColor[8][8][4];
	int CurrentPosition;
	int CurrentX;
	int CurrentY;
	int CurrentZ;
	int CurrentRed;
	int CurrentGreen;
	int CurrentBlue;
	int TopLevel;
	int BottomLevel;
public:
	LEDStringFall();
	int SuggestedNumberOfAnimationCycles();
	void StartStringFall();
	void StepStringFall();
};
#endif
