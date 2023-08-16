// LEDSprinkler.h
#ifndef LEDSprinkler_h
#define LEDSprinkler_h
#include <Arduino.h>

/*
Arc motion is defined in Move.cpp as "SprinklerArc".

Four corners.

Each corner has 3 arcs (one for each adjacent side and a third at 45 degrees toward
the cube center). Total of 12 arcs.

One arc is moved at each animation step:
Corner0, Direction0
Corner1, Direction0
Corner2, Direction0
Corner3, Direction0
Corner0, Direction1
Corner1, Direction1
Corner2, Direction1
Corner3, Direction1
Corner0, Direction2
Corner1, Direction2
Corner2, Direction2
Corner3, Direction2

Each arc has 9 positions from top to bottom.
Drops are in one of three stages and occupy positions:
(stage 0) 0, 3, 6
(stage 1) 1, 4, 7
(stage 2) 2, 5, 8

The Arc array is dimensioned as:
4 corners
3 directions in each corner
and each of the 12 arcs has:
0: Red
1: Green
2: Blue
3: drop position stage (0, 1 or 2)
*/

class LEDSprinkler {
private:
	int StepCounter;
	int StepTarget;
	int CurrentCorner;
	int CurrentDirection;
	int Arc[4][3][4];
public:
	LEDSprinkler();
	int SuggestedNumberOfAnimationCycles();
	void StartSprinkler();
	void StepSprinkler();
	void DrawArc(int Corner, int Direction, int Stage, bool Erase);
};
#endif
