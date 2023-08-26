// LEDSheets.h
#ifndef LEDSheets_h
#define LEDSheets_h
#include <Arduino.h>

/*

There are 8 vertical slots.

We pick a level at random and fill it if empty or empty it if full.

Mode:
0: Normal = sheets all have normal parallel to Z axis
1: Swap X and Z = sheets all have normal parallel to X axis
2: Swap Y and Z = sheets all have normal parallel to Y axis

Each one has a length, 3 colors and 1 of 8 possible directions:
Mode 0:
 0: +X Filling
 1: -X Filling
 2: +Y Filling
 3: -Y Filling
 4: +X Emptying
 5: -X Emptying
 6: +Y Emptying
 7: -Y Emptying
Mode 1:
 0: +Z Filling
 1: -Z Filling
 2: +Y Filling
 3: -Y Filling
 4: +Z Emptying
 5: -Z Emptying
 6: +Y Emptying
 7: -Y Emptying
Mode 2:
 0: +X Filling
 1: -X Filling
 2: +Z Filling
 3: -Z Filling
 4: +X Emptying
 5: -X Emptying
 6: +Z Emptying
 7: -Z Emptying

Second dimension of Level array:
0: Red
1: Green
2: Blue
3: Length
4: Direction

*/

class LEDSheets {
private:
	int StepCounter;
	int StepTarget;
	int CurrentLevel;
	int Level[8][5];
	int Mode;
public:
	LEDSheets();
	int SuggestedNumberOfAnimationCycles();
	void StartSheets();
	void StepSheets();
};
#endif
