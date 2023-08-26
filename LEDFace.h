// LEDFace.h
#ifndef LEDFace_h
#define LEDFace_h
#include <Arduino.h>

// #define LEDFaceMaxNumberOfCubes 10
#define LEDFaceMaxNumberOfCubes 2
/*
Each cube in the array has:
0: Face 0 orientation
1: Face 1 orientation
2: Face 2 orientation
3: Face 3 orientation
4: Face 4 orientation
5: Face 5 orientation
6: Edge length
7: X coordinate
8: Y coordinate
9: Z coordinate
10: Red
11: Green
12: Blue
13: Current brightness
14: Brightness delta
15: Current face
16: Mode
17: Active

(The explicit face orientations allow randomly animating the faces)

*/

class LEDFace {
private:
	int Mode;
	int StepCounter;
	int StepTarget;
	int StartNewCounter;
	int StartNewTarget;
	int FaceCube[LEDFaceMaxNumberOfCubes][18];
public:
	LEDFace();
	int SuggestedNumberOfAnimationCycles();
	void StartFace();
	void StepFace();
	void StartANewFaceCube();
	void AssignFaceOrientations(int CubeIndex);
	void DrawCube(int CubeIndex);
	void DrawFace(int CubeIndex, int FaceIndex);
};

#endif
