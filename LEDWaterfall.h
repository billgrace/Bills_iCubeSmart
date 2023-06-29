// LEDWaterfall.h
#ifndef LEDWaterfall_h
#define LEDWaterfall_h
#include <Arduino.h>

class LEDWaterfall {
private:
	// Segments:
	// 0: Level 7, 2x2 center ring
	// 1: Level 7, 4x4 next-to-center ring
	// 2: Level 7, 6x6 next-to-outer ring
	// 3: Level 7, 8x8 outer ring
	// 4: Level 6, 8x8 outer ring
	// 5: Level 5, 8x8 outer ring
	// 6: Level 4, 8x8 outer ring
	// 7: Level 3, 8x8 outer ring
	// 8: Level 2, 8x8 outer ring
	// 9: Level 1, 8x8 outer ring
	// 10: Level 0, 8x8 outer ring
	byte SegmentColors[11][3];
	int NumberOfCyclesToPerform;
	int CycleCounter;
	int SegmentNumber;
	int LayerNumber;
	int X;
	int Y;
	int Z;
public:
	LEDWaterfall();
	int SuggestedNumberOfAnimationCycles();
	void StartWaterfall();
	void StepWaterfall();
};
#endif
