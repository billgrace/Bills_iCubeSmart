// LEDColorRegion.h
#ifndef LEDColorRegion_h
#define LEDColorRegion_h
#include <Arduino.h>

class LEDColorRegion {
private:
	int CurrentRed;
	int CurrentGreen;
	int CurrentBlue;
	int CurrentDeltaX;
	int CurrentDeltaY;
	int CurrentDeltaZ;
	int CurrentX;
	int CurrentY;
	int CurrentZ;
	int RegionRadius;
	int OverallStepCounter;
	int OverallStepTarget;
	int CurrentColorStepCounter;
	int CurrentColorStepTarget;
	int HoldStepCounter;
	int HoldStepTarget;
public:
	LEDColorRegion();
	int SuggestedNumberOfAnimationCycles();
	void StartColorRegion();
	void StepColorRegion();
	void AddAnLED();
	void StartNewColor();
	void StartNewCenter();
};
#endif
