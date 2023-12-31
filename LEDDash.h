// LEDDash.h
#ifndef LEDDash_h
#define LEDDash_h
#include <Arduino.h>

#define DashTrailLength 20
#define DashStepsPerDim 3
#define DashStepsPerColorChange 50

class LEDDash {
private:
	int TrailWidth;
	// Each trail element has 3 location bytes, 3 color bytes, 3 direction bytes and 1 initialized flag:
	// 0 = X
	// 1 = Y
	// 2 = Z
	// 3 = Red
	// 4 = Green
	// 5 = Blue
	// 6 = DeltaX
	// 7 = DeltaY
	// 8 = DeltaZ
	// 9 = Initialized
	byte Trail[DashTrailLength][10];
	int NumberOfStepsToPerform;
	int StepCounter;
	// Direction:
	// 0 +X
	// 1 +Y
	// 2 +Z
	// 3 -X
	// 4 -Y
	// 5 -Z
	int CurrentDirection;
	int LeadRed;
	int LeadGreen;
	int LeadBlue;
public:
	LEDDash();
	int SuggestedNumberOfAnimationCycles();
	void StartDash();
	void StepDash();
	void DrawTrailElement(int Index, int Red, int Green, int Blue);
};
#endif
