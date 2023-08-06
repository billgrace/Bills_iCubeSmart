// LEDCombo8.h
#ifndef LEDCombo8_h
#define LEDCombo8_h
#include <Arduino.h>

class LEDCombo8 {
private:
public:
	LEDCombo8();
	int SuggestedNumberOfAnimationCycles();
	void StartCombo8();
	void StepCombo8();
};
#endif
