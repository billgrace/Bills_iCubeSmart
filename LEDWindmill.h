// LEDWindmill.h
#ifndef LEDWindmill_h
#define LEDWindmill_h
#include <Arduino.h>

// CenterDirection:
//	0: +X
//	1: +Y
//	2: +Z
//	3: -X
//	4: -Y
//	5: -Z
class LEDWindmill {
private:
	int Mode;
	int Red;
	int Green;
	int Blue;
	int CounterRed;
	int CounterGreen;
	int CounterBlue;
	int NewColor;
	int CenterX;
	int CenterY;
	int CenterZ;
	int CenterDirection;
	int DeltaX;
	int DeltaY;
	int CounterDeltaX;
	int CounterDeltaY;
	int Angle;
	int MaxNumberOfSteps;
	int StepCount;
	int RotationsAtEachCenter;
	int RotationCount;
	int CenterMovesPerColorChange;
	int CenterMoveCount;
public:
	LEDWindmill();
	int SuggestedNumberOfAnimationCycles();
	void StartWindmill();
	void StepWindmill();
	void DrawBlade(bool OnOrOff);
	void MoveToNextCenter();
	void TurnACorner();
};
#endif
