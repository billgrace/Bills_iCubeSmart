// LEDSlosh.h
#ifndef LEDSlosh_h
#define LEDSlosh_h
#include <Arduino.h>

class LEDSlosh {
private:
	int LeadRed;
	int LeadGreen;
	int LeadBlue;
	int TailRed;
	int TailGreen;
	int TailBlue;
	int LeadX;
	int LeadZ;
	int FastPeriod;
	int StepCounter;
	int StepTarget;
	int Stage;
	/* Tail max length = 10 */
	int TailCoordinates[10][3] = {
		{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}
	};
public:
	LEDSlosh();	
	int SuggestedNumberOfAnimationCycles();
	void StartSlosh();
	void StepSlosh();
	void DrawSlosh(bool OffOn);
	void DrawSegment(int X, int Z, int Red, int Green, int Blue);
};
#endif
