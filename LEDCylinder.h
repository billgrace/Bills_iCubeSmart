// LEDCylinder.h
#ifndef LEDCylinder_h
#define LEDCylinder_h
#include <Arduino.h>
class LEDCylinder {
private:
	int StepCounter;
	int StepTarget;
	int Angle;
	int Normal;
	int Red;
	int Green;
	int Blue;
public:
	LEDCylinder();
	int SuggestedNumberOfAnimationCycles();
	void StartCylinder();
	void StepCylinder();
	void StartANewCylinder();
};

#endif
