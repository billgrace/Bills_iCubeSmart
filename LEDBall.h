// LEDBall.h
#ifndef LEDBall_h
#define LEDBall_h
#include <Arduino.h>

/*
Segment numbering and corner numbering

The eight corners are numbered as:
0: X = 1, Y = 1, Z = 1
1: X = 6, Y = 1, Z = 1
2: X = 1, Y = 6, Z = 1
3: X = 6, Y = 6, Z = 1
4: X = 1, Y = 1, Z = 6
5: X = 6, Y = 1, Z = 6
6: X = 1, Y = 6, Z = 6
7: X = 6, Y = 6, Z = 6

The 24 segments are numbered as:
0: from corner 0 to corner 1 DeltaX = 1
1: from corner 0 to corner 2 DeltaY = 1
2: from corner 0 to corner 4 DeltaZ = 1
3: from corner 1 to corner 0 DeltaX = -1
4: from corner 1 to corner 3 DeltaY = 1
5: from corner 1 to corner 5 DeltaZ = 1
6: from corner 2 to corner 0 DeltaY = -1
7: from corner 2 to corner 3 DeltaX = 1
8: from corner 2 to corner 6 DeltaZ = 1
9: from corner 3 to corner 1 DeltaY = -1
10: from corner 3 to corner 2 DeltaX = -1
11: from corner 3 to corner 7 DeltaZ = 1
12: from corner 4 to corner 0 DeltaZ = -1
13: from corner 4 to corner 5 DeltaX = 1
14: from corner 4 to corner 6 DeltaY = 1
15: from corner 5 to corner 1 DeltaZ = -1
16: from corner 5 to corner 4 DeltaX = -1
17: from corner 5 to corner 7 DeltaY = 1
18: from corner 6 to corner 2 DeltaZ = -1
19: from corner 6 to corner 4 DeltaY = -1
20: from corner 6 to corner 7 DeltaX = 1
21: from corner 7 to corner 3 DeltaZ = -1
22: from corner 7 to corner 5 DeltaY = -1
23: from corner 7 to corner 6 DeltaX = -1

Ball style:
0: full
1: small
2: hollow outer shell
3: center LED only
4: all but center LED
*/
#define NumberOfBallStyles 5
class LEDBall {
private:
	int CenterX;
	int CenterY;
	int CenterZ;
	int BallRed;
	int BallGreen;
	int BallBlue;
	int CurrentSegmentCount;
	int MaxSegmentCount;
	int BallStyle;
public:
	LEDBall();
	int SuggestedNumberOfAnimationCycles();
	void StartBall();
	void StepBall();
	void DrawBall(int X, int Y, int Z, int Red, int Green, int Blue);
};
#endif
