// RandomSingleLED.cpp
#include <Arduino.h>
#include "LEDCube.h"
#include "LEDPlaneToCube.h"
#include "LEDPointToLine.h"
#include "LEDRandomPoints.h"
#include "LEDLinearFill.h"

extern LEDCube Cube;
extern LEDPlaneToCube PlaneToCube;
extern LEDPointToLine PointToLine;
extern LEDRandomPoints RandomPoints;
extern LEDLinearFill LinearFill;

LEDRandomPoints::LEDRandomPoints() {
}

int LEDRandomPoints::SuggestedNumberOfAnimationCycles() {
  return 1;
}

void LEDRandomPoints::StartRandomPoints() {
  // Register the start of a new animation cycle
  Cube.IncrementAnimationDurationCycleCount();
  
  Cube.ClearImage();
  StepCount = 0;
  IntroCount = 100;
  MaxPoints = random(700, 1000);
  int MinPeriod = round(5000 / MaxPoints);
  int MaxPeriod = round(8000 / MaxPoints);
  Cube.SetAnimationStepSpeedPeriodTo(random( MinPeriod, MaxPeriod));
}

// Then randomly add a new point OR erase an existing point
void LEDRandomPoints::StepRandomPoints() {
  int XYZ;
  if (StepCount <= IntroCount) {
    // For the first steps, only add new points
    Cube.SetLEDColor(Cube.RandomAxisPosition(), Cube.RandomAxisPosition(), Cube.RandomAxisPosition(), Cube.RandomColor(), Cube.RandomColor(), Cube.RandomColor());
  } else if (StepCount <= MaxPoints) {
    // After the first 100 steps, randomly add a new one or erase an existing one
    switch(random(0, 2)) {
    case 0:
      // Add a new point
      // ... Find a blank spot
      XYZ = Cube.RandomPositionWhereLEDIs(Off);
      // ... Add a new point
      if (XYZ > -1) {
        Cube.SetLEDColor(Cube.XPartOf(XYZ), Cube.YPartOf(XYZ), Cube.ZPartOf(XYZ), Cube.RandomColor(), Cube.RandomColor(), Cube.RandomColor());
      }
      break;
    case 1:
      // Erase an existing point
      // ... Find a filled spot
      XYZ = Cube.RandomPositionWhereLEDIs(On);
      // ... Erase the point there
      if (XYZ > -1) {
        Cube.SetLEDColor(Cube.XPartOf(XYZ), Cube.YPartOf(XYZ), Cube.ZPartOf(XYZ), 0, 0, 0);
      }
      break;
    }
  } else {
    // At the end, gradually extinguish the remaining points
    XYZ = Cube.RandomPositionWhereLEDIs(On);
    if (XYZ > -1) {
      Cube.SetLEDColor(Cube.XPartOf(XYZ), Cube.YPartOf(XYZ), Cube.ZPartOf(XYZ), 0, 0, 0);
    }
  }
  StepCount++;
  if (StepCount > (MaxPoints + IntroCount)) {
    StartRandomPoints();
  }
}

