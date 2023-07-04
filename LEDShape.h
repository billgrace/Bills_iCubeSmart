// LEDShape.h
#ifndef LEDShape_h
#define LEDShape_h
#include <Arduino.h>

#define MaximumNumberOfShapeShapes 8
/*
Shapes array is [shapes][character]
"character":
0: Shape type
1: Brightness
2: Color
3: X
4: Y
5: Z
Shape types:
0:	Single LED
1:	2x2 cube
2:	radius 1 solid sphere
3:	radius 1 hollow sphere
4:	3x3 cube
5:	2x2 X-normal square
6:	2x2 Y-normal square
7:	2x2 Z-normal square
8:	3x3 X-normal square
9:	3x3 Y-normal square
10:	3x3 Z-normal square
Brightness values:
0:	brightness 0 queued up to start
1:	brightness 1 increasing
2:	brightness 2 increasing
3:	brightness 3 increasing
4:	brightness 4 increasing
5:	brightness 5 increasing
6:	brightness 6 increasing
7:	brightness 7
8:	brightness 6 decreasing
9:	brightness 5 decreasing
10:	brightness 4 decreasing
11:	brightness 3 decreasing
12:	brightness 2 decreasing
13:	brightness 1 decreasing
14: brightness 0 available for re-use
Colors:
0x700: Red
0x070: Green
0x007: Blue
0x077: Cyan
0x707: Magenta
0x770: Yellow
0x777: White
*/
class LEDShape {
private:
	int StepCounter;
	int StepTarget;
	int SpawnCounter;
	int SpawnTarget;
	int NumberOfShapes;
	int StepsToNextShapeLaunch;
	int Shapes[MaximumNumberOfShapeShapes][6];
public:
	LEDShape();
	int SuggestedNumberOfAnimationCycles();
	void StartShape();
	void StepShape();
	void NudgeShape(int Index);
	void DrawShape(int ShapeType, int R, int G, int B, int X, int Y, int Z);
};
#endif
