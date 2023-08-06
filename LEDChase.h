// LEDChase.h
#ifndef LEDChase_h
#define LEDChase_h
#include <Arduino.h>

/*
Direction:
0: +X
1: -X
2: +Y
3: -Y
4: +Z
5: -Z
*/

class LEDChase {
private:
	int StepCounter;
	int StepTarget;
	int ChaseDelay[4][3] = {{3, 3, 3},{3, 3, 3},{3, 3, 3},{3, 3, 3}};
	int RunnerX;
	int RunnerY;
	int RunnerZ;
	int ChaserX;
	int ChaserY;
	int ChaserZ;
	int RunnerDeltaX;
	int RunnerDeltaY;
	int RunnerDeltaZ;
	int RunnerRed;
	int RunnerGreen;
	int RunnerBlue;
	int ChaserRed;
	int ChaserGreen;
	int ChaserBlue;
public:
	LEDChase();
	int SuggestedNumberOfAnimationCycles();
	void StartChase();
	void StepChase();
	void DrawRunner(int R, int G, int B);
	void DrawChaser(int R, int G, int B);
	void MoveRunner();
	void PickNewDirection();
};
#endif
