// LEDCube.h
#ifndef LEDCube_h
#define LEDCube_h
#include <Arduino.h>
#include <SPI.h>

// Demultiplexer (74HC138):
#define A0                  PB0     // A0
#define A1                  PB1     // A1
#define A2                  PB10    // A2
#define ANODE_ENABLE_PIN    PB11    // Anode encoder enable pin

// Shift Register (MBI5024):
#define SPI_Clock     PA5     // SPI Clock - Clock input terminal for data shift
#define SPI_MOSI      PA7     // SPI MOSI - Serial-data input to the shift register
#define LE            PC4     // LE - Latch enable
#define OE            PC5     // OE - Output enable


// How many bits specify the intensity of each LED color segment
//const int ColorDepth = 3;
//const int ColorIntensityMax = pow(2, ColorDepth) - 1;
#define ColorDepth 3
#define ColorIntensityMax pow(2, ColorDepth) - 1

// Height of cube (Z-Axis):
//const int Height = 8;
#define Height 8

// Number of rows left-to-right coordinate positions (X-Axis):
//const int XAxisPositions = 8;
#define XAxisPositions 8

// Number of primary colors: Red, Green, Blue:
//const int PrimaryColors = 3;
#define PrimaryColors 3

// To implement the color intensity a repeating series of 1 passes is made over all the LEDs in the cube. Each color segment in
//  each LED is turned on or off according to the corresponding bit in the above Cube's data. In the 1 passes, the data
//  corresponding to the least significant bit of color intensity is used once, that for the next bit twice, that for the next
//  four times, etc.
// - - - if ColorDepth is 4 bits
//const int ColorIntensityPassCount = 15;
//byte ColorIntensityIndexSelector[ColorIntensityPassCount] = {0, 3, 1, 3, 2, 3, 2, 3, 1, 3, 2, 3, 2, 3, 3};
// - - - if ColorDepth is 3 bits
//const int ColorIntensityPassCount = 7;
#define ColorIntensityPassCount 7
// moved to class declaration....byte ColorIntensityIndexSelector[ColorIntensityPassCount] = {0, 2, 1, 2, 1, 2, 2};
// - - - if ColorDepth is 2 bits
//const int ColorIntensityPassCount = 3;
//byte ColorIntensityIndexSelector[ColorIntensityPassCount] = {0, 1, 1};

// The Cube, represented by a multidimensional array of bytes (each byte lighting up a Y-Axis row of LEDs):
// If a byte is set to 0, the entire row is off.
// If a byte is 1, the frontmost LED is on.
// If a byte is 255, the entire row is on.

// "Image" is a three dimensional array storing the current colors and intensities of all the LEDs in the 8x8x8 cube.
// The first dimension ("ColorDepth") represents the brightness of a particular color in a particular LED.
// The second dimension ("Height") represents the 8 vertical levels of the cube.
// The third dimension ("ShiftRegisterBytes") is dictated by the PCB wiring of the 12 shift registers (16 bits each) and
//  their connections to the vertical wiring driving the cathodes of the LEDs. Considering a single 24-byte vector
//  representing a given color depth intensity bit and a given height level, the bytes correspond to:
//  [0] X=7 (rightmost) GREEN
//  [1] X=6 GREEN
//  [2] X=7 BLUE
//  [3] X=6 BLUE
//  [4] X=7 RED
//  [5] X=6 RED
//  [6] X=5 GREEN
//  [7] X=4 GREEN
//  [8] X=5 BLUE
//  [9] X=4 BLUE
//  [10] X=5 RED
//  [11] X=4 RED
//  [12] X=3 GREEN
//  [13] X=2 GREEN
//  [14] X=3 BLUE
//  [15] X=2 BLUE
//  [16] X=3 RED
//  [17] X=2 RED
//  [18] X=1 GREEN
//  [19] X=0 GREEN
//  [20] X=1 BLUE
//  [21] X=0 BLUE
//  [22] X=1 RED
//  [23] X=0 RED
// Within each byte, the LSB corresponds to the front LED and MSB to the rear LED.

// The shift registers which drive the LED cathodes have a bit for each of three colors in each of
// 64 LEDs on each of the 8 levels of the cube. The way the circuit board is laid out, each byte shifted
// into the shift registers controls the cathodes of one color of the 8 LEDs in one X (left/right) position.
// The least significant bit in the byte controls the front (Y=0) LED, the next bit controls the LED
// just behind it until the most significant bit controls the rear (Y=7) LED.
//const int ShiftRegisterBytes = PrimaryColors * XAxisPositions;
#define ShiftRegisterBytes PrimaryColors * XAxisPositions

class LEDCube {
  public:
    LEDCube();
    void ToggleTestMode();
    bool GetTestMode();
    void SetGlobalBoolean(bool NewValue);
    bool GetGlobalBoolean();
    void SetGlobalInteger(int NewValue);
    int GetGlobalInteger();
    void ToggleAnimationPaused();
    void SetTestAnimationIndex(int AnimationNumber);
    void SetTestAlternateIndex(int AnimationNumber);
    void SetAnimationDurationInCycles(int Cycles);
    void IncrementAnimationDurationCycleCount();
    void SetAnimationStepSpeedPeriodTo(int Period);
    void SetRandomizedAnimationStepSpeedPeriod(int Period, int RandRange);
    void AnimationStepThrottle();
    void MoveOnToNextAnimation();
    int RandomButDifferent(int ToBeAvoided, int LowEnd, int HighEnd);
    int RandomPickOfTwo(int Candidate1, int Candidate2);
    int RandomPickOfThree(int Candidate1, int Candidate2, int Candidate3);
    int RandomPickOfFour(int Candidate1, int Candidate2, int Candidate3, int Candidate4);
    int RandomPickOfEight(int Candidate1, int Candidate2, int Candidate3, int Candidate4, int Candidate5, int Candidate6, int Candidate7, int Candidate8);
    int NextIndex(int CurrentIndex, int NumberOfIndexes);
    int PreviousIndex(int CurrentIndex, int NumberOfIndexes);
    int RandomColor();
    int CompositeColor(int Red, int Green, int Blue);
    int RedPartOf(int CompositeColor);
    int GreenPartOf(int CompositeColor);
    int BluePartOf(int CompositeColor);
    int NearbyColor(int Red, int Green, int Blue, int Distance);
    int VeryCloseColor(int Red, int Green, int Blue);
    int VeryDifferentColor(int Red, int Green, int Blue);
    int SumOfThreeColors(int Color1, int Color2, int Color3);
    int DimmerColor(int Color);
    int RandomSolidColor();
    int RandomAxisPosition();
    int RandomDeltaPosition();
    int CompositePosition(int X, int Y, int Z);
    int RandomPositionWhereLEDIs(bool OnOrOff);
    int RandomPositionWhereLEDIsOn();
    int RandomPositionWhereLEDIsOff();
    int NearbyCoordinate(int Coordinate, int Distance);
    int XPartOf(int CompositePosition);
    int YPartOf(int CompositePosition);
    int ZPartOf(int CompositePosition);
    int CenterBias(int Position);
    void ClearImage();
    void FillLayer(int Layer, int Red, int Green, int blue);
    bool ThisLEDIsOn(int X, int Y, int Z);
    void SetLEDColor(int XLeftToRight, int YFrontToBack, int ZBottomToTop, int Red, int Green, int Blue);
    int GetLEDColor(int XLeftToRight, int YFrontToBack, int ZBottomToTop);
    void RenderImageToPhysicalCube();
    void SwitchToLayer(int z);
    void ClearCurrentLayer();
    void PaintRainbow();
    int RedXCoordinateToShiftRegisterByteIndex(int X);
    int GreenXCoordinateToShiftRegisterByteIndex(int X);
    int BlueXCoordinateToShiftRegisterByteIndex(int X);
    int YCoordinateToBitMask(int Y);
  private:
    bool TestMode;
    bool AnimationPaused;
    bool GlobalBoolean = false;
    int GlobalInteger = 0;
    int AnimationStepSpeedPeriod = 0;
    int AnimationStepSpeedCounter = 0;
    int AnimationDurationInCycles = 0;
    int AnimationDurationCycleCounter = 0;
    int TestAnimationIndex = 0;
    int TestAlternateIndex = 0;
    int CurrentAnimationIndex = 0;
    int LastAnimationIndex = 0;
    int NumberOfAnimationsImplemented = 28;
    int RecentAnimationIndexes[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    byte LEDIsOn[8][8][8];
    byte ColorIntensityIndexSelector[ColorIntensityPassCount] = {0, 2, 1, 2, 1, 2, 2};
    byte Image[ColorDepth][Height][ShiftRegisterBytes];
    byte RainbowImage[ColorDepth][Height][ShiftRegisterBytes] =
      {{
      // G  G  B  B  R  R  G  G  B  B  R  R  G  G  B  B  R  R  G  G  B  B  R  R
      {0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255}, // Red = all Red
      {0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255}, // Orange = Red + 1/4 Green
      {255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255}, // Yellow = Red + Green
      {255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0}, // Green = all Green
      {255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0}, // Cyan = Green + Blue
      {0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0}, // Blue = all Blue
      {0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255}, // Magenta = Red + Blue
      {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}, // White = Red + Green + Blue
      },{
      {0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255}, // Red = all Red
      {255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255}, // Orange = Red + 1/4 Green
      {255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255}, // Yellow = Red + Green
      {255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0}, // Green = all Green
      {255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0}, // Cyan = Green + Blue
      {0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0}, // Blue = all Blue
      {0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255}, // Magenta = Red + Blue
      {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}, // White = Red + Green + Blue
      },{
      {0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255}, // Red = all Red
      {0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255}, // Orange = Red + 1/4 Green
      {255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255}, // Yellow = Red + Green
      {255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0}, // Green = all Green
      {255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0}, // Cyan = Green + Blue
      {0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 255, 255, 0, 0}, // Blue = all Blue
      {0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255, 0, 0, 255, 255, 255, 255}, // Magenta = Red + Blue
      {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}, // White = Red + Green + Blue
      }};
};

#endif
