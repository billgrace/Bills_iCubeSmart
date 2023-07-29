// LEDLoopFill.h

#ifndef LEDLoopFill_h
#define LEDLoopFill_h
#include <Arduino.h>

/*
Each loop consists of 12 LEDs starting at a face. It proceeds "inward" for
3 steps then angles for two more then one step orthogonally then backs out
symetrically.
Step = 0: First LED near face edge
Step = 1: Second LED moving inward
Step = 2: Third LED moving inward
Step = 3: Fourth LED moving inward
Step = 4: Fifth LED moving diagonally "in-up"
Step = 5: Sixth LED moving diagonally "in-up"
Step = 6: Seventh LED moving orthogonaly "up"
Step = 7: Eighth LED moving diagonally "out-up"
Step = 8: Ninth LED moving diagonally "out-up"
Step = 9: Tenth LED moving outward
Step = 10: Eleventh LED moving outward
Step = 11: Twelfth LED moving outward

Each loop begins and ends on one of the 6 faces of the cube. It has one
of 4 orientations with respect to each face.

Faces:
0: +X
1: -X
2: +Y
3: -Y
4: +Z
5: -Z

Orientations:
0: Up
1: Right
2: Down
3: Left
*/

class LEDLoopFill {
private:
	int LoopCounter;
	int LoopTarget;
	int FaceCounter;
	int FaceTarget;
	int Step;
	int Face;
	int Orientation;
	int Offset1;
	int Offset2;
	int Red;
	int Green;
	int Blue;
	int X;
	int Y;
	int Z;
	int DeltaX;
	int DeltaY;
	int DeltaZ;
	int Coordinate[12][2] = {
		{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 1}, {5, 2},
		{5, 3}, {4, 4}, {3, 5}, {2, 5}, {1, 5}, {0, 5}
	};
public:
	LEDLoopFill();
	int SuggestedNumberOfAnimationCycles();
	void StartLoopFill();
	void StepLoopFill();
	void StartALoop();
	void StartAFace();
};
#endif
