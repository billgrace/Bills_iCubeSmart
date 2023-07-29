// LEDMarathon.h
#ifndef LEDMarathon_h
#define LEDMarathon_h
#include <Arduino.h>

#define MarathonTrailLength 10
#define MarathonStepsPerDim 2

class LEDMarathon {
private:
	int StepCounter;
	int StepTarget;
	int ColorChangeCounter;
	int ColorChangeTarget;
	int DirectionChangeCounter;
	int DirectionChangeTarget;
	int Direction;
	/* Each trail element has 3 bytes of location and 3 bytes of color
	0: X
	1: Y
	2: Z
	3: Red
	4: Green
	5: Blue
	*/
	byte Trail[MarathonTrailLength][6];
	int LeadCompositeColor;
	int LeadRed;
	int LeadGreen;
	int LeadBlue;
public:
	LEDMarathon();
	int SuggestedNumberOfAnimationCycles();
	void StartMarathon();
	void StepMarathon();
};

#endif
