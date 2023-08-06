// LEDLightning.h

#ifndef LEDLightning_h
#define LEDLightning_h
#include <Arduino.h>

class LEDLightning {
private:
	int StepCounter;
	int StepTarget;
	int StrikeCounter;
	int StrikeTarget;
	int GrayLevel;
	int StrikeX;
	int StrikeY;
	int StrikeZ;
	bool StrikeActive;
public:
	LEDLightning();
	int SuggestedNumberOfAnimationCycles();
	void StartLightning();
	void StepLightning();
	void StartStrike();
	void StepStrike();
};
#endif
