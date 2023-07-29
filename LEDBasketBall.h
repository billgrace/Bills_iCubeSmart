// LEDBasketBall.h
#ifndef LEDBasketBall_h
#define LEDBasketBall_h
#include <Arduino.h>

/*
Put a hoop in a corner or middle of a side.
Set the shooter opposite the hoop.
Pick hoop and shooter heights between Z=3 and Z=5.
The hoop will always be a hollow square 3 LEDs on a side. The
hoop extends from HoopX-1, HoopY-1 to HoopX+1, HoopY+1.
The ball is a single LED. It arcs from the shooter to the
hoop and completes the cycle when it passes through the hoop. The
ball passes through the hoop at HoopX, HoopY.
The ball arc starts at "Stage1" during which it rises from
its initial height to 2 above that. Stage 2 has the ball
travelling horizontally to directly above the hoop. Stage 3
is the ball dropping through the hoop. When it gets to 2
below the hoop, the cycle is complete.
*/

class LEDBasketBall {
private:
	int Stage;
	int BallRed;
	int BallGreen;
	int BallBlue;
	int HoopRed;
	int HoopGreen;
	int HoopBlue;
	int HoopX;
	int HoopY;
	int HoopZ;
	int BallX;
	int BallY;
	int BallZ;
	int Stage2DeltaX;
	int Stage2DeltaY;
	int Stage2Z;
public:
	LEDBasketBall();
	int SuggestedNumberOfAnimationCycles();
	void StartBasketBall();
	void StepBasketBall();
};
#endif
