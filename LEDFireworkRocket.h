// LEDFireworkRocket.h
#ifndef LEDFireworkRocket_h
#define LEDFireworkRocket_h
#include <Arduino.h>

// rough map of arc point numbers:
//		0	1	2	3	4	5	6	7
//
// 7			8					14
//
// 6		7		9			13
//
// 5	6			12	10	12
//
// 4	5			12	11	12
//
// 3	4			12	12	12	
//
// 2	3		13				13
//
// 1	2	14						14
//
// 0	1
//
class LEDFireworkRocket {
private:
	// SegmentNumber:
	//		0: Arc
	//		1: Fireball expansion & arc fading
	//		2: Fireball shimmering
	// ArcStageNumber:
	//		0: Rising
	//		1: Curving
	//		2: Falling
	// FireballStageNumber:
	//		0: Center
	//		1: Shell1
	//		2: Shell2
	//		3: Shell3
	// ShimmerStageNumber:
	//		0: Breathing
	//		1: Fading
	int SegmentNumber;
	int ArcStageNumber;
	int FireballStageNumber;
	int ShimmerStageNumber;
	void StartArc();
	int ArcPointNumber;
	int ArcSpeed;
	int ArcRed;
	int ArcGreen;
	int ArcBlue;
	int ArcX;
	int ArcY;
	int ArcZ;
	int ArcDeltaX;
	int ArcDeltaY;
	int ArcDeltaZ;
	void StartFireball();
	void FireballCenter(int X, int Y, int Z, int Red, int Green, int Blue);
	void FireballShell1(int X, int Y, int Z, int Red, int Green, int Blue);
	void FireballShell2(int X, int Y, int Z, int Red, int Green, int Blue);
	void FireballShell3(int X, int Y, int Z, int Red, int Green, int Blue);
	int FireballSpeed;
	int FireballCenterRed;
	int FireballCenterGreen;
	int FireballCenterBlue;
	int FireballShell1Red;
	int FireballShell1Green;
	int FireballShell1Blue;
	int FireballShell2Red;
	int FireballShell2Green;
	int FireballShell2Blue;
	int FireballShell3Red;
	int FireballShell3Green;
	int FireballShell3Blue;
	void StartShimmering();
	int ShimmerSpeed;
	int ShimmerCounter;
public:
	LEDFireworkRocket();
	int SuggestedNumberOfAnimationCycles();
	void StartFireworkRocket();
	void StepFireworkRocket();
};

#endif
