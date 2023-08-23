// LEDBigSlosh.h
#ifndef LEDBigSlosh_h
#define LEDBigSlosh_h
#include <Arduino.h>

/*
*/
class LEDBigSlosh {
private:
	int StepCounter;
	int StepTarget;
public:
	LEDBigSlosh();
	int SuggestedNumberOfAnimationCycles();
	void StartBigSlosh();
	void StepBigSlosh();
};

#endif
