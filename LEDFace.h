// LEDFace.h
#ifndef LEDFace_h
#define LEDFace_h
#include <Arduino.h>

class LEDFace {
private:
	int StepCounter;
	int StepTarget;
	int CurrentFace;
	int FaceOrientation[6];
	int Red;
	int Green;
	int Blue;
public:
	LEDFace();
	int SuggestedNumberOfAnimationCycles();
	void StartFace();
	void StepFace();
	void PickFaceOrientations();
	void PickColors();
	void DrawFace(int Index);
};

#endif
