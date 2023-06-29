// LEDRandomPoints.h
#ifndef LEDRandomPoints_h
#define LEDRandomPoints_h
#include <Arduino.h>

class LEDRandomPoints {
  private:
    int StepCount;
    int IntroCount;
    int MaxPoints;
  public:
    LEDRandomPoints();
    int SuggestedNumberOfAnimationCycles();
    void StartRandomPoints();
    void StepRandomPoints();
};

#endif
