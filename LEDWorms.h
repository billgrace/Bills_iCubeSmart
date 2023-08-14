// LEDWorms.h

#ifndef LEDWorms_h
#define LEDWorms_h
#include <Arduino.h>

#define LEDWormMaximumNumberOfWorms 8
#define LEDWormMaximumWormLength 20

/*
WormParameters array second dimension:
0: WormLength
1: WormMaximumLength
2: DirectionOfGrowth - 0 is +X, 1 is -X, etc.

WormSegment array third dimension:
0: X
1: Y
2: Z
3: Red
4: Green
5: Blue
*/

class LEDWorms {
private:
	int StepCounter;
	int StepTarget;
	int NumberOfWorms;
	int CurrentWorm;
	int WormParameters[LEDWormMaximumNumberOfWorms][3];
	int WormSegment[LEDWormMaximumNumberOfWorms][LEDWormMaximumWormLength][6];
public:
	LEDWorms();
	int SuggestedNumberOfAnimationCycles();
	void StartWorms();
	void StepWorms();
	void StartAWorm(int WormIndex);
	void AddNewHeadSegment(int WormIndex);
	void EraseLastSegment(int WormIndex);
	int PickANewDirection(int OldDirection, int OldX, int OldY, int OldZ);
	void DrawWorm(int WormIndex);
};
#endif
