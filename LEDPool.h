// LEDPool.h
#ifndef LEDPool_h
#define LEDPool_h
#include <Arduino.h>

/*
Four separate pools, one in each bottom corner.
Pipe rises to top and then showers toward bottom.
Each corner has its own color.
Corner numbering:
0: X = 0, Y = 0
1: X = 7, Y = 0
2: X = 7, Y = 7
3: X = 0, Y = 7

Drops rise from the pools, arc toward center and drop to a center pool.

CurrentCorner rotates through 0..3. When this # matches one of the four
corner pools, a drop rises from that pool.
*/

class LEDPool {
private:
	int CompositeColor;
	int Colors[4][3];
	int StepCounter;
	int StepTarget;
	int DrippingCorner;
	int PoolHeight;
	int PoolHeightCounter;
	int PoolHeightTarget;
	int ArcLength;
	int ArcPoints[14][3] = {
		{0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6}, {1, 1, 7}, 
		{2, 2, 7}, {3, 3, 6}, {3, 3, 5}, {3, 3, 4}, {3, 3, 3}, {3, 3, 2}, {3, 3, 1}
	};
public:
	LEDPool();	
	int SuggestedNumberOfAnimationCycles();
	void StartPool();
	void StepPool();
	void DrawCornerPool(int Corner);
	void DrawCenterPool(int Red, int Green, int Blue);
	void DrawArcs(bool OffOn);
};
#endif
