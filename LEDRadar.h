// LEDRadar.h
#ifndef LEDRadar_h
#define LEDRadar_h
#include <Arduino.h>

/*
Mode:
0: solid rectangle
1: solid "triangle"
2: outline rectangle
3: outline "triangle"
*/

class LEDRadar {
private:
	int StepCounter;
	int StepTarget;
	int Angle;
	int Mode;
	int Red;
	int Green;
	int Blue;
public:
	LEDRadar();
	int SuggestedNumberOfAnimationCycles();
	void StartRadar();
	void StepRadar();
	void DrawBeam(int Red, int Green, int Blue);
	void DrawVertical(int Radius, int X, int Y, int Red, int Green, int Blue);
};
#endif
