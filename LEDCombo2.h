// LEDCombo2.h
#ifndef LEDCombo2_h
#define LEDCombo2_h
#include <Arduino.h>

class LEDCombo2 {
private:
public:
	LEDCombo2();
	int SuggestedNumberOfAnimationCycles();
	void StartCombo2();
	void StepCombo2();
};
#endif