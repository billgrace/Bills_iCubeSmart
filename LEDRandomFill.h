// LEDRandomFill.h
#ifndef LEDRandomFill_h
#define LEDRandomFill_h
#include <Arduino.h>

class LEDRandomFill {
private:
	int StepCounter;
	int StepTarget;
public:
	LEDRandomFill();
	int SuggestedNumberOfAnimationCycles();
	void StartRandomFill();
	void StepRandomFill();
};
#endif
