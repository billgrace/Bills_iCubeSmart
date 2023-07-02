// LEDShape.h
#ifndef LEDShape_h
#define LEDShape_h
#include <Arduino.h>

class LEDShape {
private:
public:
	LEDShape();
	int SuggestedNumberOfAnimationCycles();
	void StartShape();
	void StepShape();
};
#endif
