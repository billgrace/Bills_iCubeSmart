// LEDStarrySky.h
#ifndef LEDStarrySky_h
#define LEDStarrySky_h
#include <Arduino.h>

class LEDStarrySky {
private:
	int NumberOfStars;
	int InitialTwinkleStagger;
	int StepCount;
	int IntroCount;
	int MaxSteps;
	bool TimeToQuit;
	// 0 => this location is off
	// 1..7 => this location is on and brightening
	// 8..14 => this location is on and dimming
	int StarState[8][8][8];
	int XYZ;
	int X;
	int Y;
	int Z;
	int Red;
	int Green;
	int Blue;
	int PresentBrightness;
public:
	LEDStarrySky();
	int SuggestedNumberOfAnimationCycles();
	void StartStarrySky();
	void StepStarrySky();
	bool ArrayIsEmpty();
	int NextStarBrightness(int X, int Y, int Z);
	void StartAStarAt(int X, int Y, int Z);
};
#endif