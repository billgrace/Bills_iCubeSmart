// LEDMovingAxes.h
#ifndef LEDMovingAxes_h
#define LEDMovingAxes_h
#include <Arduino.h>

/*
Mode 0: Moving axes
Mode 1: Moving planes
In mode 1 the X axis becomes an XY plane,
  the Y axis becomes a YZ plane and
  the Z axis becomes a ZX plane.
*/

class LEDMovingAxes {
private:
	int Mode[3];
	int AxisColorChangeInterval;
	int StepCount;
	int MaxStepCount;
	int NumberOfAxisSets;
	int X1AxisRed;
	int X1AxisGreen;
	int X1AxisBlue;
	int Y1AxisRed;
	int Y1AxisGreen;
	int Y1AxisBlue;
	int Z1AxisRed;
	int Z1AxisGreen;
	int Z1AxisBlue;
	int X1AxisPosition;
	int Y1AxisPosition;
	int Z1AxisPosition;
	int CurrentMotionAxis1;
	int CurrentMotionDirection1;
	int MotionModeAxis1;
	int MotionModeAngle1;
	int MotionDirectionChangeInterval1;
	int X2AxisRed;
	int X2AxisGreen;
	int X2AxisBlue;
	int Y2AxisRed;
	int Y2AxisGreen;
	int Y2AxisBlue;
	int Z2AxisRed;
	int Z2AxisGreen;
	int Z2AxisBlue;
	int X2AxisPosition;
	int Y2AxisPosition;
	int Z2AxisPosition;
	int CurrentMotionAxis2;
	int CurrentMotionDirection2;
	int MotionModeAxis2;
	int MotionModeAngle2;
	int MotionDirectionChangeInterval2;
	int X3AxisRed;
	int X3AxisGreen;
	int X3AxisBlue;
	int Y3AxisRed;
	int Y3AxisGreen;
	int Y3AxisBlue;
	int Z3AxisRed;
	int Z3AxisGreen;
	int Z3AxisBlue;
	int X3AxisPosition;
	int Y3AxisPosition;
	int Z3AxisPosition;
	int CurrentMotionAxis3;
	int CurrentMotionDirection3;
	int MotionModeAxis3;
	int MotionModeAngle3;
	int MotionDirectionChangeInterval3;
public:
	LEDMovingAxes();
	int SuggestedNumberOfAnimationCycles();
	int SetMotionDirectionChangeInterval(int MotionMode);
	void StartMovingAxes();
	void StepMovingAxes();
	int NextPosition1(int CurrentPosition);
	int NextPosition2(int CurrentPosition);
	int NextPosition3(int CurrentPosition);
	void DrawAxes(bool Erase);
};
#endif
