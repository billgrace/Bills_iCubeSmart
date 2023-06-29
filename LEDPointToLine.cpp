// LEDPointToLine.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDPointToLine.h"

extern LEDCube Cube;
extern LEDPointToLine PointToLine;

LEDPointToLine::LEDPointToLine() {
  XIncrement = 1;
  YIncrement = 1;
  ZIncrement = 1;
}

int LEDPointToLine::SuggestedNumberOfAnimationCycles() {
  return random(15, 25);
}

void LEDPointToLine::StartPointToLine() {
  // Register the start of a new animation cycle
  Cube.IncrementAnimationDurationCycleCount();
  
  Cube.ClearImage();

  // Pick a random color
  Red = random(0, 8);
  Green = random(0, 8);
  Blue = random(0, 8);

  // Pick a line length
  FullLineLength = random( 3, 9);

  // Pick a sort-of-random animation speed
  // Line length    Period
  //      3           100
  //      4           90
  //      5           80
  //      6           70
  //      7           60
  //      8           50

  switch(FullLineLength) {
  case 1:
    Cube.SetAnimationStepSpeedPeriodTo(150);
    break;
  case 2:
    Cube.SetAnimationStepSpeedPeriodTo(120);
    break;
  case 3:
    Cube.SetAnimationStepSpeedPeriodTo(100);
    break;
  case 4:
    Cube.SetAnimationStepSpeedPeriodTo(90);
    break;
  case 5:
    Cube.SetAnimationStepSpeedPeriodTo(80);
    break;
  case 6:
    Cube.SetAnimationStepSpeedPeriodTo(70);
    break;
  case 7:
    Cube.SetAnimationStepSpeedPeriodTo(60);
    break;
  case 8:
    Cube.SetAnimationStepSpeedPeriodTo(50);
    break;
  }

  // Pick a line origin and direction
  int MaxMinX = 8 - FullLineLength;
  MinX = random(0, MaxMinX + 1);
  MaxX = MinX + FullLineLength - 1;
  MinY = random(0, MaxMinX + 1);
  MaxY = MinY + FullLineLength - 1;
  MinZ = random(0, MaxMinX + 1);
  MaxZ = MinZ + FullLineLength - 1;
  switch(random(0, 8)) {
    case 0:
      CurrentX = MinX;
      CurrentY = MinY;
      CurrentZ = MinZ;
      XIncrement = 1;
      YIncrement = 1;
      ZIncrement = 1;
      break;
    case 1:
      CurrentX = MinX;
      CurrentY = MinY;
      CurrentZ = MaxZ;
      XIncrement = 1;
      YIncrement = 1;
      ZIncrement = -1;
      break;
    case 2:
      CurrentX = MinX;
      CurrentY = MaxY;
      CurrentZ = MinZ;
      XIncrement = 1;
      YIncrement = -1;
      ZIncrement = 1;
      break;
    case 3:
      CurrentX = MaxX;
      CurrentY = MinY;
      CurrentZ = MinZ;
      XIncrement = -1;
      YIncrement = 1;
      ZIncrement = 1;
      break;
    case 4:
      CurrentX = MinX;
      CurrentY = MaxY;
      CurrentZ = MaxZ;
      XIncrement = 1;
      YIncrement = -1;
      ZIncrement = -1;
      break;
    case 5:
      CurrentX = MaxX;
      CurrentY = MinY;
      CurrentZ = MaxZ;
      XIncrement = -1;
      YIncrement = 1;
      ZIncrement = -1;
      break;
    case 6:
      CurrentX = MaxX;
      CurrentY = MaxY;
      CurrentZ = MinZ;
      XIncrement = -1;
      YIncrement = -1;
      ZIncrement = 1;
      break;
    case 7:
      CurrentX = MaxX;
      CurrentY = MaxY;
      CurrentZ = MaxZ;
      XIncrement = -1;
      YIncrement = -1;
      ZIncrement = -1;
      break;
  }
  CurrentLineLength = 0;
}

void LEDPointToLine::StepPointToLine() {
  Cube.SetLEDColor( CurrentX, CurrentY, CurrentZ, Red, Green, Blue );
  CurrentLineLength++;
  if (CurrentLineLength >= FullLineLength) {
    StartPointToLine();
  } else {
    CurrentX = CurrentX + XIncrement;
    CurrentY = CurrentY + YIncrement;
    CurrentZ = CurrentZ + ZIncrement;
  }
}
