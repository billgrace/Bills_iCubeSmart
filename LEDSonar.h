// LEDSonar.h
#ifndef LEDSonar_h
#define LEDSonar_h
#include <Arduino.h>

#define MaxNumberOfSonarBlips 10
/* Each sonar blip has:
0: X
1: Y
2: Z
3: Red
4: Green
5: Blue
6: Size
7: State

where State is:
0: Center only, attenuation 0
1: Center only, attenuation 1
2: Center plus shell 1, attenuation 2
3: Center plus shell 1, attenuation 3
4: Center off, shell 1, attenuation 4
5: Shell 1 plus shell 2, attenuation 5
6: Shell 1 off, shell 2, attenuation 6
7: All off, available
*/

class LEDSonar {
private:
	int StepCounter;
	int StepTarget;
	int StartCounter;
	int StartTarget;
	int SonarBlip[MaxNumberOfSonarBlips][8];
public:
	LEDSonar();
	int SuggestedNumberOfAnimationCycles();
	void StartSonar();
	void StepSonar();
	void StartNewBlip();
	void StepAllActiveBlips();
	void DrawCenter(int X, int Y, int Z, int Red, int Green, int Blue, int Attenuation);
	void DrawShell1(int X, int Y, int Z, int Red, int Green, int Blue, int Attenuation);
	void DrawShell2(int X, int Y, int Z, int Red, int Green, int Blue, int Attenuation);
};
#endif
