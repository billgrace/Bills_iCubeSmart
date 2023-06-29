// LEDPong.h
#ifndef LEDPong_h
#define LEDPong_h
#include <Arduino.h>

/*
Pong shapes:
0: single LED
1: 3 x 3 solid cube
2: 3 x 3 solid ball
3: 5 x 5 solid cube
4: 5 x 5 solid ball
5: 3 x 3 hollow cube
6: 3 x 3 hollow ball
7: 5 x 5 hollow cube
8: 5 x 5 hollow ball
*/
#define NumberOfPongShapes 9
#define MaximumNumberOfPongSteps 250
class LEDPong {
private:
	int PongShape;
	int PongRadius;
	int PongStepLength;
	int PongStepCounter;
	int PongRed;
	int PongGreen;
	int PongBlue;
	int LapStepCounter;
	int LapStepTarget;
public:
	LEDPong();
	int SuggestedNumberOfAnimationCycles();
	void StartPong();
	void StepPong();
	void DrawPong(int X, int Y, int Z, int Red, int Green, int Blue);
	void DrawPongBall2(int X, int Y, int Z, int Red, int Green, int Blue);
	void DrawPongBall3(int X, int Y, int Z, int Red, int Green, int Blue);
};
#endif
