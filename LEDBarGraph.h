// LEDBarGraph.h
#ifndef LEDBarGraph_h
#define LEDBarGraph_h
#include <Arduino.h>

/*
Either 4 4x4 bars or 16 2x2 bars
"Row" is a line in the X-axis direction
"Column" is a line in the Y-axis direction
Each bar has an X, Y location, a color, a max height, a current height and
	a motion state:
			0 => not moving
			1 => going up
			2 => going down

Bar array is 16 (# of bars) by 8:
	0: X
	1: Y
	2: Red
	3: Green
	4: Blue
	5: max top level
	6: current top level
	7: state

Mode:
	0 => only single bars moving
	1 => all the bars moving
	2 => one row of bars moving
	3 => one column of bars moving
*/
class LEDBarGraph {
private:
	int StepCounter;
	int StepTarget;
	int Mode;
	int EdgeSize;
	int BarsPerAxis;
	int BarsInUse;
	int MinTopLevel;
	int MoveOnCounter;
	int MoveOnTarget;
	int CurrentRow;
	int CurrentColumn;
	int Bar[16][8];
public:
	LEDBarGraph();
	int SuggestedNumberOfAnimationCycles();
	void StartBarGraph();
	void StepBarGraph();
	void StartBar(int Index);
	void MoveBar(int Index);
	void DrawBarLevel(int Index, int Level, bool Erase);
};
#endif
