// LEDColumns.h

#ifndef LEDColumns_h
#define LEDColumns_h
#include <Arduino.h>

class LEDColumns {
private:
	int ColumnCounter;
	int ColumnTarget;
	int Red;
	int Green;
	int Blue;
	int Direction;
	int Length;
	int X;
	int Y;
	int Z;
public:
	LEDColumns();
	int SuggestedNumberOfAnimationCycles();
	void StartColumns();
	void StepColumns();
	void StartAColumn();
};
#endif
