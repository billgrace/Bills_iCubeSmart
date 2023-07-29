// LEDJumpRope.h
#ifndef LEDJumpRope_h
#define LEDJumpRope_h
#include <Arduino.h>

class LEDJumpRope {
private:
	int StepCounter;
	int StepTarget;
	int RopeColorChangeCounter;
	int RopeColorChangeTarget;
	int KidColorChangeCounter;
	int KidColorChangeTarget;
	int Direction;
	int Angle;
	int RopeRed;
	int RopeGreen;
	int RopeBlue;
	int KidRed;
	int KidGreen;
	int KidBlue;
public:
	LEDJumpRope();
	int SuggestedNumberOfAnimationCycles();
	void StartJumpRope();
	void StepJumpRope();
	void DrawScene(int RRed, int RGreen, int RBlue, int KRed, int KGreen, int KBlue);
	void ShowRope(int Radius, int X, int Z, int Red, int Green, int Blue);
	void DrawKid(int Z, int Red, int Green, int Blue);
};
#endif
