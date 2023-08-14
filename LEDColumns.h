// LEDColumns.h

#ifndef LEDColumns_h
#define LEDColumns_h
#include <Arduino.h>

/*
Mode:
0 => just keep lighting up columns
1 => alternate between lighting up and erasing columns
2 => light up columns for the first half then erase for the second half
*/

class LEDColumns {
private:
	int ColumnCounter;
	int ColumnTarget;
	int Mode;
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
