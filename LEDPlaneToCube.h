// PlaneToCube.h
#ifndef LEDPlaneToCube_h
#define LEDPlaneToCube_h
#include <Arduino.h>

/*
CurrentNormalAxis:
  0 => +X
  1 => -X
  2 => +Y
  3 => -Y
  4 => +Z
  5 => -Z
*/

class LEDPlaneToCube {
	public:
		LEDPlaneToCube();
		int SuggestedNumberOfAnimationCycles();
	    void StartPlaneToCube();
	    void StepPlaneToCube();
	private:
		int CurrentNormalAxis;
		int CubeEdgeSize;
		int MinX;
		int MaxX;
		int CurrentX;
		int MinY;
		int MaxY;
		int CurrentY;
		int MinZ;
		int MaxZ;
		int CurrentZ;
		int XIncrement;
		int YIncrement;
		int ZIncrement;
		int Red;
		int Green;
		int Blue;
};

#endif
