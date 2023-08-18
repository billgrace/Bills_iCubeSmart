// LEDWireCube.h
#ifndef LEDWireCube_h
#define LEDWireCube_h
#include <Arduino.h>

class LEDWireCube {
private:
	int StepCounter;
	int StepTarget;
	int ColorChangeCounter;
	int ColorChangeTarget;
	int EdgeLength;
	int EdgeLengthDelta;
	int Red;
	int Green;
	int Blue;
public:
	LEDWireCube();
	int SuggestedNumberOfAnimationCycles();
	void StartWireCube();
	void StepWireCube();
	void DrawCube(bool Erase);
};

#endif
