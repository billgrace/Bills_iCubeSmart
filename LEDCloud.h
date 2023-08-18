// LEDCloud.h
#ifndef LEDCloud_h
#define LEDCloud_h
#include <Arduino.h>

#define LEDCloudMaxNumberOfClouds 10
/*
Each cloud has:
0: Red
1: Green
2: Blue
3: EdgeLength
4: X (lower front left)
5: Y (lower front left)
6: Z (lower front left)
7: Brightness
8: Brightness delta
*/
class LEDCloud {
private:
	int StepCounter;
	int StepTarget;
	int StartNewCounter;
	int StartNewTarget;
	int Cloud[LEDCloudMaxNumberOfClouds][9];
public:
	LEDCloud();
	int SuggestedNumberOfAnimationCycles();
	void StartCloud();
	void StepCloud();
	void StartANewCloud();
	void DrawCloud(int Index);
};

#endif
