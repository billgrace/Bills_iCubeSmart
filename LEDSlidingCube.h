// LEDSlidingCube.h
#ifndef LEDSlidingCube_h
#define LEDSlidingCube_h
#include <Arduino.h>

/*
Two modes:
Mode 0: fill the LED cube leaving one empty sub-cube and slide an empty sub-cube around
Mode 1: fill the LED cube entirely and vary the sub-cube colors for a while
Two cube sizes:
64 cubes, 2 LEDs on a side
8 cubes, 4 LEDs on a side
An array of 64 cube colors has an index that starts at position 0, 0, 0
	and increments in the +X direction first, then the +Y direction next
	and finally the +Z direction.
Stage 1 adds cubes until all but one are full.
Stage 2 moves the empty space by randomly picking an adjacent
	cube and sliding it into the empty space.
*/

class LEDSlidingCube {
private:
	int StepCounter;
	int StepCountTarget;
	int Mode;
	int Stage;
	int NumberOfCubes;
	int EmptyIndex;
	int SourceIndex;
	int NewEmptyIndex;
	int XOffset;
	int YOffset;
	int ZOffset;
	int SlideDirection;
	int SlideOffset;
	int EdgeLength;
	int Colors[64][3];
public:
	LEDSlidingCube();
	int SuggestedNumberOfAnimationCycles();
	void StartSlidingCube();
	void StepSlidingCube();
	void DrawACube(int Index);
	void PickASourceIndex();
	void SlideTheCubeOneStep();
	void DrawOneSlice(int NormalAxis, int CornerX, int CornerY, int CornerZ, int Red, int Green, int Blue);
	int GetCornerCompositeCoordinate(int Index);
	bool ThereIsACubePlusX();
	bool ThereIsACubeMinusX();
	bool ThereIsACubePlusY();
	bool ThereIsACubeMinusY();
	bool ThereIsACubePlusZ();
	bool ThereIsACubeMinusZ();
};
#endif
