// LEDBinary.h
#ifndef LEDBinary_h
#define LEDBinary_h
#include <Arduino.h>

/*
Use the "Cube move" motion to animate the center
point of a pair of orbiting objects.
Elaborate by adding symmetrically located orbiting
pairs to get 2 or 4 (or maybe 8?) pairs in all.
*/
class LEDBinary {
private:
	int StepCounter;
	int StepTarget;
	int AngleStepCounter;
	int AngleStepsPerCenterMove;
	int NumberOfCenters;
	int NextNumberOfCenters;
	int ChangeNumberOfCentersCounter;
	int ChangeNumberOfCentersTarget;
	int Angles[8];
	int Colors[16][3];
	int Center0X;
	int Center0Y;
	int Center0Z;
public:
	LEDBinary();
	int SuggestedNumberOfAnimationCycles();
	void StartBinary();
	void StepBinary();
	void DrawCenters(bool OffOn);
	void DrawCenter(int CenterIndex, int X, int Y, int Z, bool OffOn);
	void DrawObject(int ObjectIndex, int X, int Y, int Z, bool OffOn);
	int GetXOffset(int angle);
	int GetYOffset(int angle);
};

#endif
