// LEDCorner.h
#ifndef LEDCorner_h
#define LEDCorner_h
#include <Arduino.h>

/*
Each expanding corner has a corner number for location (see move.h),
  a color, a duration at each size, a final size and a duration before being erased.
  The color will also vary while it persists at the final size.
0: Corner number
1: Red
2: Green
3: Blue
4: Present size
5: Target steps at each size
6: Count of steps at present size
7: Final size
8: Target steps at final size
9: Count of steps at final size
*/

class LEDCorner {
private:
	int StepCounter;
	int StepTarget;
	int StartCounter;
	int StartTarget;
	int NumberOfCorners;
	int Corner[8][10];
public:
	LEDCorner();
	int SuggestedNumberOfAnimationCycles();
	void StartCorner();
	void StepCorner();
	void StartACorner();
	void DrawCorner(int CornerNumber, int Size, int Red, int Green, int Blue);
};
#endif
