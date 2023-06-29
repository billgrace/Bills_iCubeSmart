// LEDTide.h
#ifndef LEDTide_h
#define LEDTide_h
#include <Arduino.h>

class LEDTide {
private:
	int TwinkleStepCount;
	int LevelStepDirection;
	int TwinkleLevel;
	int SolidLevel;
	int LevelColor [8][3];
	int CleanupX;
	int CleanupY;
	int CleanupZ;
public:
	LEDTide();
	int SuggestedNumberOfAnimationCycles();
	void StartTide();
	void InitializeTwinkleCount();
	void CleanupNext();
	bool NextCleanupPosition();
	void MoveUp();
	void MoveDown();
	void StepTide();
};

#endif
