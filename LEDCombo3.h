// LEDCombo3.h
#ifndef LEDCombo3_h
#define LEDCombo3_h
#include <Arduino.h>

class LEDCombo3 {
private:
public:
	LEDCombo3();
	int SuggestedNumberOfAnimationCycles();
	void StartCombo3();
	void StepCombo3();
};
#endif
