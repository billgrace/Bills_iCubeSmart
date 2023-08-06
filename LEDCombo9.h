// LEDCombo9.h
#ifndef LEDCombo9_h
#define LEDCombo9_h
#include <Arduino.h>

class LEDCombo9 {
private:
public:
	LEDCombo9();
	int SuggestedNumberOfAnimationCycles();
	void StartCombo9();
	void StepCombo9();
};
#endif
