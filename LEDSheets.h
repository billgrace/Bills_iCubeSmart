// LEDSheets.h
#ifndef LEDSheets_h
#define LEDSheets_h
#include <Arduino.h>

/*

There are 8 vertical slots.

We pick a level at random and fill it if empty or empty it if full.

Each one has a length, 3 colors and 1 of 8 possible directions:
0: +X Filling
1: -X Filling
2: +Y Filling
3: -Y Filling
4: +X Emptying
5: -X Emptying
6: +Y Emptying
7: -Y Emptying

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
public:
	LEDSheets();
	int SuggestedNumberOfAnimationCycles();
	void StartSheets();
	void StepSheets();
};
#endif
