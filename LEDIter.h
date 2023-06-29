// LEDIter.h
#ifndef LEDIter_h
#define LEDIter_h
#include <Arduino.h>

/*
Stages:
0: Center cube, 8 LEDs
1: Bottom front leg, 8 LEDs
2: Bottom right leg, 7 LEDs
3: Bottom rear leg, 7 LEDs
4: Bottom left leg, 7 LEDs
5: Top front leg, 8 LEDs
6: Top right leg, 7 LEDs
7: Top rear leg, 7 LEDs
8: Top left leg, 7 LEDs
9: Front lower left diagonal, 2 LEDs
10: Front lower right diagonal
11: Front upper left diagonal
12: Front upper right diagonal
13: Rear lower left diagonal
14: Rear lower right diagonal
15: Rear upper left diagonal
16: Rear upper right diagonal
17: Fuel put in place in position0
18: Fuel rotate to position1
19: Fuel rotate to position2
20: Fuel rotate to position3
21: Fuel rotate to position0
*/

class LEDIter {
private:
	int CurrentFuelSpeed;
	int TargetFuelSpeed;
	int StageNumber;
	int LEDNumber;
	int FrameRed;
	int FrameGreen;
	int FrameBlue;
	int FuelRed;
	int FuelGreen;
	int FuelBlue;
	int StepCounter;
	int StepTarget;
public:
	LEDIter();
	int SuggestedNumberOfAnimationCycles();
	void StartIter();
	void StepIter();
	void DrawFuelCube(int X, int Y, int Z, bool OffOn);
};
#endif
