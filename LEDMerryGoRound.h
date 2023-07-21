// LEDMerryGoRound.h
#ifndef LEDMerryGoRound_h
#define LEDMerryGoRound_h
#include <Arduino.h>

#define MerryGoRoundMaximumNumberOfHorsies 4
/*
Each horsie has:
0: MinHeight
1: MaxHeight
2: CurrentHeight
3: DeltaHeight;
4: Red
5: Green
6: Blue
*/
class LEDMerryGoRound {
private:
	int StepCounter;
	int StepTarget;
	int MoveCounter;
	int MoveTarget;
	int EdgeSize;
	int NumberOfHorsies;
	int Horsie[MerryGoRoundMaximumNumberOfHorsies][4];
public:
	LEDMerryGoRound();
	int SuggestedNumberOfAnimationCycles();
	void StartMerryGoRound();
	void StepMerryGoRound();
	void DrawHorsies(bool Erase);
	void DrawHorsie(int Left, int Front, int HorsieHeight, int Red, int Green, int Blue);
};

#endif
