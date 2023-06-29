// LEDRandomFull.h
#ifndef LEDRandomFull_h
#define LEDRandomFull_h
#include <Arduino.h>

class LEDRandomFull {
private:
	int MaxNumberOfSteps;
	int StepCount;
public:
	LEDRandomFull();
	int SuggestedNumberOfAnimationCycles();
	void StartRandomFull();
	void StepRandomFull();
};

#endif
