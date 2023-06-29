// LEDSpiral.h
#ifndef LEDSpiral_h
#define LEDSpiral_h
#include <Arduino.h>

class LEDSpiral {
private:
	// Axis direction:
	// 0: +X
	// 1: +Y
	// 2: +Z
	// 3: -X
	// 4: -Y
	// 5: -Z
	int AxisDirection;
	int AxisPosition1;
	int AxisPosition2;
	int CurrentPosition;
	int VaryTheColor;
	int Red;
	int Green;
	int Blue;
public:
	LEDSpiral();
	int SuggestedNumberOfAnimationCycles();
	void StartSpiral();
	void StepSpiral();
};
#endif
