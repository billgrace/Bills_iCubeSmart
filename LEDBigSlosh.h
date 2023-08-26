// LEDBigSlosh.h
#ifndef LEDBigSlosh_h
#define LEDBigSlosh_h
#include <Arduino.h>

/*
Pick X or Y as a pivot axis. (Axis == 0 means Y is pivot, Axis == 1 means it's X)

Vary thickness and position along that axis.

Start with a column along one side that's 8 high and 3 wide.
Each step remove a layer from the top and add a layer to the bottom/side.
Do the same to climb the opposite wall then reverse the whole process.

It's 5 steps to go from along one side to along the bottom and another
5 steps to climb the opposite wall. Add 10 more for the reverse and
we get 20 total steps to return to the original position.

"Angle" tracks progress along those 20 steps.

"Position" specifies 5 horizontal slabs along the starting vertical wall,
8 vertical slabs along the bottom and 5 slabs along the opposite vertical wall.

Pivot between X and Y by simply swapping those two coordinates.
*/
class LEDBigSlosh {
private:
	int StepCounter;
	int StepTarget;
	int CurrentAngle;
	int CurrentDirection;
	int Red;
	int Green;
	int Blue;
	int Axis;
	int Width;
	int Offset;
public:
	LEDBigSlosh();
	int SuggestedNumberOfAnimationCycles();
	void StartBigSlosh();
	void StepBigSlosh();
	void DrawSlab(int Position, int Red, int Green, int Blue);
};

#endif
