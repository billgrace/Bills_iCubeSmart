// LEDPinWheel.h
#ifndef LEDPinWheel_h
#define LEDPinWheel_h
#include <Arduino.h>
class LEDPinWheel {
private:
	int StepCounter;
	int StepTarget;
	int StartNewCounter;
	int StartNewTarget;
	int Mode;
	int Angle;
	int Normal;
	int Length;
	int CurrentOffset;
	int MaxOffset;
	int OffsetDelta;
	int Red;
	int Green;
	int Blue;
public:
	LEDPinWheel();
	int SuggestedNumberOfAnimationCycles();
	void StartPinWheel();
	void StepPinWheel();
	void StartANewPinWheel();
	void DrawArm(int ArmAngle, int Red, int Green, int Blue);
};

#endif
