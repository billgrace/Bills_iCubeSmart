// LEDMove.h
#ifndef LEDMove_h
#define LEDMove_h
#include <Arduino.h>

/*
#####################################################
#####################################################
#############   CUBE MOVE   #########################
#####################################################
#####################################################
Move a center from one corner of the LED cube to another, then another.
Allow a configurable space from the corner to the center.

CubeMoveMode:
	0 => randomly traverse all the edges of the cube
	1 => rotate around the edges of the X = 0 plane, then to X = 7 & back
	2 => rotate around the edges of the Y = 0 plane, then to Y = 7 & back
	3 => rotate around the edges of the Z = 0 plane, then to Z = 7 & back

CubeMoveSegmentCounter/Target = how long before switching to the other side.


#####################################################
#####################################################
#############   SPIRAL MOVE #########################
#####################################################
#####################################################
Move along one of several patterns to fill an 8 x 8 plane.


#####################################################
#####################################################
#############   HINGE MOVE  #########################
#####################################################
#####################################################
Swing one face of the LED cube to another, then another...

3 Axes are numbered:
0: X
1: Y
2: Z

8 Corners are numbered:
Corner#	X	Y	Z
0		0	0	0
1		7	0	0
2		0	7	0
3		7	7	0
4		0	0	7
5		7	0	7
6		0	7	7
7		7	7	7

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

The 6 faces (normal points inward toward center of cube) are numbered as:
0: Normal +X (right), corners 0, 2, 4, 6 - segments 1, 6, 2, 12, 8, 18, 14, 19 - hinges 1, 2, 6, 9
1: Normal +Y (further), corners 0, 1, 4, 5 - segments 0, 3, 2, 12, 5, 15, 13, 16 - hinges 0, 2, 4, 8
2: Normal +Z (up), corners 0, 1, 2, 3 - segments 0, 3, 4, 9, 1, 6, 7, 10 - hinges 0, 1, 3, 5
3: Normal -X (left), corners 1, 3, 5, 7 - segments 1, 6, 8, 18, 8, 18, 14, 19 - hinges 3, 4, 7, 10
4: Normal -Y (closer), corners 2, 3, 6, 7 - segments 7, 10, 11, 21, 8, 18, 20, 23 - hinges 5, 6, 7, 11
5: Normal -Z (down), corners 4, 5, 6, 7 - segments 13, 16, 14, 19, 17, 22, 20, 23 - hinges 8, 9, 10, 11

The 12 hinges (non-directional segments) are numberer as:
0: between corners 0 and 1 (segments 0 and 3) (faces 1 and 2)
1: between corners 0 and 2 (segments 1 and 6) (faces 0 and 2)
2: between corners 0 and 4 (segments 2 and 12) (faces 0 and 1)
3: between corners 1 and 3 (segments 4 and 9) (faces 2 and 3)
4: between corners 1 and 5 (segments 5 and 15) (faces 1 and 3)
5: between corners 2 and 3 (segments 7 and 10) (faces 2 and 4)
6: between corners 2 and 6 (segments 8 and 18) (faces 0 and 4)
7: between corners 3 and 7 (segments 11 and 21) (faces 3 and 4)
8: between corners 4 and 5 (segments 13 and 16) (faces 1 and 5)
9: between corners 4 and 6 (segments 14 and 19) (faces 0 and 5)
10: between corners 5 and 7 (segments 17 and 22) (faces 3 and 5)
11: between corners 6 and 7 (segments 20 and 23) (faces 4 and 5)

The 24 swivels are numbered as:
0: from face 0 to face 1
1: from face 0 to face 2
2: from face 0 to face 4
3: from face 0 to face 5
4: from face 1 to face 0
5: from face 1 to face 2
6: from face 1 to face 3
7: from face 1 to face 5
8: from face 2 to face 0
9: from face 2 to face 1
10: from face 2 to face 3
11: from face 2 to face 4
12: from face 3 to face 1
13: from face 3 to face 2
14: from face 3 to face 4
15: from face 3 to face 5
16: from face 4 to face 0
17: from face 4 to face 2
18: from face 4 to face 3
19: from face 4 to face 5
20: from face 5 to face 0
21: from face 5 to face 1
22: from face 5 to face 3
23: from face 5 to face 4


#####################################################
#####################################################
#############   PONG MOVE  ##########################
#####################################################
#####################################################
Move diagonally until coming within a configuarable distance
from a face of the LED cube then reflect away from the face.


#####################################################
#####################################################
#############   SLOSH MOVE  #########################
#####################################################
#####################################################
A pattern of motion in one of the side faces of the LED cube
where a point climbs from the bottom of one side of the face
to the top and then "falls" down again and runs across the
bottom to the other side of the face. The move routines
provide both a horizontal and vertical coordinate and
a time factor allowing a sense of gravity in the motion.

The 19 slosh positions and speeds (period multiplier "M"):
0:  X = 7, Z = 0, M = 1
1:  X = 7, Z = 1, M = 2
2:  X = 7, Z = 2, M = 4
3:  X = 7, Z = 3, M = 6
4:  X = 7, Z = 4, M = 9
5:  X = 7, Z = 5, M = 13
6:  X = 7, Z = 6, M = 16
7:  X = 7, Z = 7, M = 20
8:  X = 6, Z = 7, M = 25
9:  X = 6, Z = 6, M = 20
10: X = 6, Z = 5, M = 16
11: X = 6, Z = 4, M = 13
12: X = 6, Z = 3, M = 9
13: X = 6, Z = 2, M = 6
14: X = 5, Z = 1, M = 4
15: X = 4, Z = 0, M = 2
16: X = 3, Z = 0, M = 1
17: X = 2, Z = 0, M = 1
18: X = 1, Z = 0, M = 1


#####################################################
#####################################################
#############   ROTOR MOVE  #########################
#####################################################
#####################################################
Start with a horizontal line running from one corner of
the a face of the LED cube to the opposite corner. Rotate
the line through 180 degrees in a series of 14 moves to
give the appearance of a spinning rotor.

There are 14 rotor angles corresponding to outer LED positions:
angle	outer LED position
0		0, 0
1		1, 0
2		2, 0
3		3, 0
4		4, 0
5		5, 0
6		6, 0
7		7, 0
8		7, 1
9		7, 2
10		7, 3
11		7, 4
12		7, 5
13		7, 6

Each angle indexes into an array of eight X, Y coordinate pairs locating
 the 8 points of the rotor bar at that angle.


#####################################################
#####################################################
#############   CIRCLE MOVE  #########################
#####################################################
#####################################################
Move in a (rough) circle circumscribed within an 8x8 face.

There are 12 points that *kind of* make such a circle:
0		4, 0
1		6, 1
2		7, 3
3		7, 4
4		6, 6
5		4, 7
6		3, 7
7		1, 6
8		0, 4
9		0, 3
10		1, 1
11		3, 0


#####################################################
#####################################################
#############   MERRYGOROUND MOVE   #################
#####################################################
#####################################################
Move around the outside of the bottom layer.
The motion supported is that of a single point at
the "front left" (smallest X & Y) of a variable-size
square.
The minimum possible coordinate is always 0.
The maximum possible coordinate is 8 - the edge size of the square
MerryGoRoundCurrentDirection:
0: X=0->max, Y=0
1: X=max, Y=0->max
2: X=max->0, Y=max
3: X=0, Y=max->0
4: X=max->0, Y=0
5: X=0, Y=0->max
6: X=0->max, Y=max
7: X=max, Y=max->0


#####################################################
#####################################################
##############   MARATHON MOVE   ####################
#####################################################
#####################################################
Move around the outer X/Y edges at Z = 0. Then increment
Z and do it again. Repeat till Z = 7 then keep going
with Z decrementing.
It's up to the calling routine to handle any variations
in axis assignments and polarities.
MarathonMoveSegment:
0: X moves from 0 to 7 with Y at 0
1: Y moves from 0 to 7 with X at 7
2: X moves from 7 to 0 with Y at 7
3: Y moves from 7 to 0 with X at 0

*/
#define NumberOfSpiralPatterns 4
class LEDMove {
private:
	int ObjectRadius;
	int MinPosition;
	int MaxPosition;
	int CurrentCubeMoveX;
	int CurrentCubeMoveY;
	int CurrentCubeMoveZ;
	int CurrentPongMoveX;
	int CurrentPongMoveY;
	int CurrentPongMoveZ;
	int CubeMoveMode;
	int NewX;
	int NewY;
	int NewZ;
	int CurrentCubeSegmentNumber;
	int CubeMoveSegmentCounter;
	int CubeMoveSegmentTarget;
	int DeltaX;
	int DeltaY;
	int DeltaZ;
	int CurrentSpiralPattern;
	int SpiralPositions[NumberOfSpiralPatterns][64][2] = {
		{
			{3, 3}, {4, 3}, {4, 4}, {3, 4},	{2, 4}, {2, 3}, {2, 2}, {3, 2}, 
			{4, 2}, {5, 2}, {5, 3}, {5, 4}, {5, 5},	{4, 5}, {3, 5}, {2, 5}, 
			{1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1},	{2, 1}, {3, 1}, {4, 1}, 
			{5, 1}, {6, 1},	{6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6},	{5, 6},
			{4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6},	{0, 5}, {0, 4}, {0, 3}, 
			{0, 2}, {0, 1}, {0, 0},	{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, 
			{6, 0}, {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, 
			{7, 7}, {6, 7}, {5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7} 
		},
		// {
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, },
		// 	{, }, {, }, {, }, {, }, {, }, {, }, {, }, {, }
		// },
		{
			{0, 7}, {1, 7}, {2, 7}, {3, 7}, {3, 6}, {2, 6}, {1, 6}, {0, 6},
			{0, 5}, {1, 5}, {2, 5}, {3, 5}, {3, 4}, {2, 4}, {1, 4}, {0, 4},
			{0, 3}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, {1, 1}, {1, 2}, {1, 3},
			{2, 3}, {2, 2}, {2, 1}, {2, 0}, {3, 0}, {3, 1}, {3, 2}, {3, 3},
			{4, 3}, {4, 2}, {4, 1}, {4, 0}, {5, 0}, {5, 1}, {5, 2}, {5, 3},
			{6, 3}, {6, 2}, {6, 1}, {6, 0}, {7, 0}, {7, 1}, {7, 2}, {7, 3},
			{7, 4}, {6, 4}, {5, 4}, {4, 4}, {4, 5}, {5, 5}, {6, 5}, {7, 5},
			{7, 6}, {6, 6}, {5, 6}, {4, 6}, {4, 7}, {5, 7}, {6, 7}, {7, 7}
		},
		{
			{0, 7}, {0, 6}, {1, 7}, {2, 7},	{1, 6}, {0, 5}, {0, 4}, {1, 5}, 
			{2, 6}, {3, 7}, {4, 7}, {3, 6}, {2, 5}, {1, 4}, {0, 3}, {0, 2}, 
			{1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}, {6, 7}, {5, 6}, {4, 5}, 
			{3, 4}, {2, 3},	{1, 2}, {0, 1}, {0, 0}, {1, 1}, {2, 2}, {3, 3},
			{4, 4}, {5, 5}, {6, 6}, {7, 7}, {7, 6}, {6, 5}, {5, 4}, {4, 3}, 
			{3, 2}, {2, 1}, {1, 0}, {2, 0}, {3, 1}, {4, 2}, {5, 3}, {6, 4}, 
			{7, 5}, {7, 4}, {6, 3}, {5, 2}, {4, 1}, {3, 0}, {4, 0}, {5, 1}, 
			{6, 2}, {7, 3}, {7, 2}, {6, 1}, {5, 0}, {6, 0}, {7, 1}, {7, 0} 
		},
		{
			{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7},
			{1, 7}, {1, 6}, {1, 5}, {1, 4}, {1, 3}, {1, 2}, {1, 1}, {1, 0},
			{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7},
			{3, 7}, {3, 6}, {3, 5}, {3, 4}, {3, 3}, {3, 2}, {3, 1}, {3, 0},
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7},
			{5, 7}, {5, 6}, {5, 5}, {5, 4}, {5, 3}, {5, 2}, {5, 1}, {5, 0},
			{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7},
			{7, 7}, {7, 6}, {7, 5}, {7, 4}, {7, 3}, {7, 2}, {7, 1}, {7, 0}
		}
	};
	int FromFace;
	int ToFace;
	int CurrentHinge;
	int PreviousHinge;
	int CurrentSwivel;
	int HingePositions[7][8][2] = {
		{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
		{{0, 0}, {0, 1}, {1, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {2, 7}},
		{{0, 0}, {0, 1}, {1, 2}, {2, 3}, {3, 4}, {3, 5}, {4, 6}, {4, 7}},
		{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
		{{0, 0}, {1, 0}, {2, 1}, {3, 2}, {4, 3}, {5, 3}, {6, 4}, {7, 4}},
		{{0, 0}, {1, 0}, {2, 1}, {3, 1}, {4, 1}, {5, 2}, {6, 2}, {7, 2}},
		{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}}
	};
	#define SloshMoveIndexCount 19
	int SloshIndex;
	int SloshPositionsAndSpeeds[SloshMoveIndexCount][3] = {
		{7, 0, 1}, {7, 1, 2}, {7, 2, 3}, {7, 3, 5}, {7, 4, 7}, 
		{7, 5, 9}, {7, 6, 11}, {7, 7, 13}, {6, 7, 12}, {6, 6, 11}, 
		{6, 5, 9}, {6, 4, 7}, {6, 3, 5}, {6, 2, 3}, {5, 1, 2}, 
		{4, 0, 1}, {3, 0, 1}, {2, 0, 1}, {1, 0, 1}
	};
	#define RotorMoveAngleCount 14
	int RotorMoveBarCoordinates[RotorMoveAngleCount][8][2] = {
		{
			{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}
		},
		{
			{1, 0}, {2, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {5, 6}, {6, 7}
		},
		{
			{2, 0}, {2, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {5, 6}, {5, 7}
		},
		{
			{3, 0}, {3, 1}, {3, 2}, {3, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}
		},
		{
			{4, 0}, {4, 1}, {4, 2}, {4, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}
		},
		{
			{5, 0}, {5, 1}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {2, 6}, {2, 7}
		},
		{
			{6, 0}, {6, 1}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {1, 7}
		},
		{
			{7, 0}, {6, 1}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {0, 7}
		},
		{
			{7, 1}, {6, 1}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {1, 6}, {0, 6}
		},
		{
			{7, 2}, {6, 2}, {5, 2}, {4, 3}, {3, 4}, {2, 5}, {1, 5}, {0, 5}
		},
		{
			{7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 4}, {2, 4}, {1, 4}, {0, 4}
		},
		{
			{7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 3}, {2, 3}, {1, 3}, {0, 3}
		},
		{
			{7, 5}, {6, 5}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 2}, {0, 2}
		},
		{
			{7, 6}, {6, 6}, {5, 5}, {4, 4}, {3, 3}, {2, 2}, {1, 1}, {0, 1}
		}
	};
	int CircleMovePositions[12][2] = {
		{4, 0}, {6, 1}, {7, 3}, {7, 4}, {6, 6}, {4, 7}, {3, 7}, {1, 6}, {0, 4}, {0, 3}, {1, 1}, {3, 0}
	};
	int MerryGoRoundMoveEdgeSize;
	int MerryGoRoundMaxCoordinate;
	int MerryGoRoundCurrentDirection;
	int MerryGoRoundMoveX;
	int MerryGoRoundMoveY;
	int MarathonMoveX;
	int MarathonMoveY;
	int MarathonMoveZ;
	int MarathonMoveSegment;
	int MarathonMoveVerticalDirection;
public:
	LEDMove();
	void InitializeCubeMove(int Radius, int Mode, int SegmentCountTarget);
	bool AtEndOfCurrentCubeMoveSegment();
	void AdvanceToNextCubeMovePosition();
	int GetCurrentCubeMoveX();
	int GetCurrentCubeMoveY();
	int GetCurrentCubeMoveZ();
	int GetCubeMoveDeltaX();
	int GetCubeMoveDeltaY();
	int GetCubeMoveDeltaZ();
	void SetupNextCubeMoveSegment();
	void StartCubeMoveSegment();
	void SetSpiralMovePattern(int Pattern);
	int GetSpiralMovePosition0(int Index);
	int GetSpiralMovePosition1(int Index);
	void InitializeHingeMove();
	void SetupNextHingeFace();
	int GetCurrentSwivel();
	int GetHingePosition0(int Angle, int Index);
	int GetHingePosition1(int Angle, int Index);
	void InitializePongMove(int Radius);
	void StepPongMove();
	int GetCurrentPongMoveX();
	int GetCurrentPongMoveY();
	int GetCurrentPongMoveZ();
	void InitializeSloshMove();
	void StepSloshMove();
	int GetSloshX();
	int GetSloshZ();
	int GetSloshM();
	bool SloshIsAtBeginning();
	bool SloshIsAtEnd();
	int GetRotorMoveX(int Angle, int BarPoint);
	int GetRotorMoveY(int Angle, int BarPoint);
	int GetCircleMoveX(int Angle);
	int GetCircleMoveY(int Angle);
	void InitializeMerryGoRoundMove(int EdgeSize);
	void StepMerryGoRoundMove();
	int GetMerryGoRoundMoveX();
	int GetMerryGoRoundMoveY();
	void InitializeMarathonMove();
	void StepMarathonMove();
	int GetMarathonMoveX();
	int GetMarathonMoveY();
	int GetMarathonMoveZ();
};
#endif
