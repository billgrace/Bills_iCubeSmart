// LEDLineFill.h

#ifndef LEDLineFill_h
#define LEDLineFill_h
#include <Arduino.h>

class LEDLineFill {
private:
	int LineCounter;
	int LineTarget;
	int Red;
	int Green;
	int Blue;
	int X;
	int Y;
	int Z;
	int DeltaX;
	int DeltaY;
	int DeltaZ;
public:
	LEDLineFill();
	int SuggestedNumberOfAnimationCycles();
	void StartLineFill();
	void StepLineFill();
	void StartALine();
};
#endif
