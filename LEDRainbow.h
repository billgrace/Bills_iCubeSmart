// LEDRainbow.h
#ifndef LEDRainbow_h
#define LEDRainbow_h
#include <Arduino.h>

class LEDRainbow {
private:
	int StepCounter;
	int StepTarget;
	int Direction;
	int Stage;
	int Colors[8][3] = {
		{7, 0, 0}, // Red
		{7, 2, 0}, // Orange
		{7, 7, 0}, // Yellow
		{0, 7, 0}, // Green
		{0, 0, 7}, // Blue
		{0, 7, 7}, // Cyan
		{7, 0, 7}, // Magenta
		{7, 7, 7}  // White
	};
public:
	LEDRainbow();
	int SuggestedNumberOfAnimationCycles();
	void StartRainbow();
	void StepRainbow();
};
#endif
