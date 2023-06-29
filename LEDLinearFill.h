// LEDLinearFill.h
#ifndef LEDLinearFill_h
#define LEDLinearFill_h
#include <Arduino.h>

class LEDLinearFill {
	private:
		int Red;
		int Green;
		int Blue;
		int RedGradient;
		int GreenGradient;
		int BlueGradient;
		int X;
		int Y;
		int Z;
	public:
		LEDLinearFill();
		int SuggestedNumberOfAnimationCycles();
		void StartLinearFill();
		void StepLinearFill();
};

#endif
