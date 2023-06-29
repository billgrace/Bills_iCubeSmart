// PointToLine.h
#ifndef LEDPointToLine_h
#define LEDPointToLine_h
#include <Arduino.h>

class LEDPointToLine {
  public:
    LEDPointToLine();
    int SuggestedNumberOfAnimationCycles();
    void StartPointToLine();
    void StepPointToLine();
  private:
    int FullLineLength;
    int CurrentLineLength;
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
