// LEDFountain.h
#ifndef LEDFountain_h
#define LEDFountain_h
#include <Arduino.h>

class LEDFountain {
private:
	// Segments:
	// 0: Level 0, 8x8 outer ring
	// 1: Level 0, 6x6 next-to-outer ring
	// 2: Level 1, 6x6 next-to-outer ring & 4x4 next-to-inner ring
	// 3: Level 2, 4x4 next-to-inner ring & 2x2 inner ring
	// 4: Level 3, 2x2 inner ring
	// 5: Level 4, 2x2 inner ring
	// 6: Level 5, 2x2 inner ring
	// 7: Level 6, 2x2 inner ring
	// 8: Level 7, 2x2 inner ring
	// 9: Level 7, 4x4 next-to-inner ring
	// 10: Level 7, 6x6 next-to-outer ring
	// 11: Level 7, 8x8 outer ring
	// 12: Level 6, four corners
	// 13: Level 5, four corners
	// 14: Level 4, four corners
	// 15: Level 3, four corners
	// 16: Level 2, four corners
	// 17: Level 1, four corners
	byte SegmentColors[18][3];
	int NumberOfCyclesToPerform;
	int CycleCounter;
	int SegmentNumber;
	int X;
	int Y;
	int Z;
public:
	LEDFountain();
	int SuggestedNumberOfAnimationCycles();
	void StartFountain();
	void StepFountain();
};
#endif
