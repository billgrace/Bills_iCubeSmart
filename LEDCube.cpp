// LEDCube.cpp

#include <Arduino.h>
#include <SPI.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDPlaneToCube.h"
#include "LEDPointToLine.h"
#include "LEDRandomPoints.h"
#include "LEDLinearFill.h"
#include "LEDFireworkRocket.h"
#include "LEDTide.h"
#include "LEDBall.h"
#include "LEDRandomFull.h"
#include "LEDStarrySky.h"
#include "LEDFountain.h"
#include "LEDWaterfall.h"
#include "LEDWindmill.h"
#include "LEDDash.h"
#include "LEDSpiral.h"
#include "LEDStringFall.h"
#include "LEDFlopWall.h"
#include "LEDPong.h"
#include "LEDMovingAxes.h"
#include "LEDColorRegion.h"
#include "LEDSlidingCube.h"
#include "LEDIter.h"
#include "LEDSLosh.h"
#include "LEDPool.h"
#include "LEDRotor.h"
#include "LEDBinary.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDPlaneToCube PlaneToCube;
extern LEDPointToLine PointToLine;
extern LEDRandomPoints RandomPoints;
extern LEDLinearFill LinearFill;
extern LEDFireworkRocket FireworkRocket;
extern LEDTide Tide;
extern LEDBall Ball;
extern LEDRandomFull RandomFull;
extern LEDStarrySky StarrySky;
extern LEDFountain Fountain;
extern LEDWaterfall Waterfall;
extern LEDWindmill Windmill;
extern LEDDash Dash;
extern LEDSpiral Spiral;
extern LEDStringFall StringFall;
extern LEDFlopWall FlopWall;
extern LEDPong Pong;
extern LEDMovingAxes MovingAxes;
extern LEDColorRegion ColorRegion;
extern LEDSlidingCube SlidingCube;
extern LEDIter Iter;
extern LEDSlosh Slosh;
extern LEDPool Pool;
extern LEDRotor Rotor;
extern LEDBinary Binary;

LEDCube::LEDCube() {
  TestMode = false;
  TestAnimationIndex = 0;
  TestAlternateIndex = 1;

  // Shift Register:
  pinMode(SPI_Clock, OUTPUT);
  pinMode(SPI_MOSI, OUTPUT);
  pinMode(LE, OUTPUT);
  pinMode(OE, OUTPUT);

  // RGB anode demultiplexer:
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(ANODE_ENABLE_PIN, OUTPUT);

  ClearImage();
}

void LEDCube::ToggleTestMode() {
  TestMode = !TestMode;
}

bool LEDCube::GetTestMode() {
  return TestMode;
}

void LEDCube::SetGlobalBoolean(bool NewValue) {
  GlobalBoolean = NewValue;
}

bool LEDCube::GetGlobalBoolean() {
  return GlobalBoolean;
}

void LEDCube::SetGlobalInteger(int NewValue) {
  GlobalInteger = NewValue;
}

int LEDCube::GetGlobalInteger() {
  return GlobalInteger;
}

void LEDCube::ToggleAnimationPaused() {
  AnimationPaused = !AnimationPaused;
}

void LEDCube::SetTestAnimationIndex(int AnimationNumber) {
  TestAnimationIndex = AnimationNumber;
}

void LEDCube::SetTestAlternateIndex(int AnimationNumber) {
  TestAlternateIndex = AnimationNumber;
}

void LEDCube::SetAnimationDurationInCycles(int Cycles) {
  AnimationDurationInCycles = Cycles;
  AnimationDurationCycleCounter = 0;
}

void LEDCube::IncrementAnimationDurationCycleCount() {
  AnimationDurationCycleCounter++;
}

void LEDCube::SetAnimationStepSpeedPeriodTo(int Period) {
  AnimationStepSpeedPeriod = Period;
  AnimationStepSpeedCounter = 0;
}

void LEDCube::SetRandomizedAnimationStepSpeedPeriod(int Period, int RandRange) {
  int MinimumRandomParameter = max(Period - RandRange, 2);
  AnimationStepSpeedPeriod = random(MinimumRandomParameter, Period + RandRange);
  AnimationStepSpeedCounter = 0;
}

void LEDCube::AnimationStepThrottle() {
  if (AnimationPaused){
    return;
  }
  if (AnimationDurationCycleCounter > AnimationDurationInCycles) {
    MoveOnToNextAnimation();
  } else {
    AnimationStepSpeedCounter++;
    if (AnimationStepSpeedCounter > AnimationStepSpeedPeriod) {
      AnimationStepSpeedCounter = 0;
      switch(CurrentAnimationIndex) {
      case 0:
        PlaneToCube.StepPlaneToCube();
        break;
      case 1:
        PointToLine.StepPointToLine();
        break;
      case 2:
        RandomPoints.StepRandomPoints();
        break;
      case 3:
        LinearFill.StepLinearFill();
        break;
      case 4:
        FireworkRocket.StepFireworkRocket();
        break;
      case 5:
        Tide.StepTide();
        break;
      case 6:
        Ball.StepBall();
        break;
      case 7:
        RandomFull.StepRandomFull();
        break;
      case 8:
        StarrySky.StepStarrySky();
        break;
      case 9:
        Fountain.StepFountain();
        break;
      case 10:
        Waterfall.StepWaterfall();
        break;
      case 11:
        Windmill.StepWindmill();
        break;
      case 12:
        Dash.StepDash();
        break;
      case 13:
        Spiral.StepSpiral();
        break;
      case 14:
        StringFall.StepStringFall();
        break;
      case 15:
        FlopWall.StepFlopWall();
        break;
      case 16:
        Pong.StepPong();
        break;
      case 17:
        MovingAxes.StepMovingAxes();
        break;
      case 18:
        ColorRegion.StepColorRegion();
        break;
      case 19:
        SlidingCube.StepSlidingCube();
        break;
      case 20:
        Iter.StepIter();
        break;
      case 21:
        Slosh.StepSlosh();
        break;
      case 22:
        Pool.StepPool();
        break;
      case 23:
        Rotor.StepRotor();
        break;
      default:
      case 24:
        Binary.StepBinary();
        break;
        Serial1.println("Default case in AnimationStepThrottle()");
        break;
      }
    }
  }
}

void LEDCube::MoveOnToNextAnimation() {
bool CandidateIndexIsRecent;
bool NonRecentIndexHasBeenFound;
int CandidateAnimationIndex;
  if (TestMode) {
    // In test mode, alternate between the animation under test and some other designated "alternate"
    if (CurrentAnimationIndex == TestAnimationIndex) {
      CurrentAnimationIndex = TestAlternateIndex;
    } else {
      CurrentAnimationIndex = TestAnimationIndex;
    }
  } else {
    // In nomal mode, keep track of the 10 most recently run animations and pick some other to run next
    // first, save the just-run animation in the list of recents
    for (int i = 9; i > 0; i--) {
      RecentAnimationIndexes[i] = RecentAnimationIndexes[i - 1];
    }
    RecentAnimationIndexes[0] = CurrentAnimationIndex;
    // Then try random animation indexes until we get one that's not on the list of recents
    NonRecentIndexHasBeenFound = false;
    while (false == NonRecentIndexHasBeenFound) {
      CandidateAnimationIndex = random(0, NumberOfAnimationsImplemented);
      CandidateIndexIsRecent = false;
      for (int i = 0; i < 10; i++) {
        if (RecentAnimationIndexes[i] == CandidateAnimationIndex) {
          CandidateIndexIsRecent = true;
        }
      }
      if (CandidateIndexIsRecent == false) {
        NonRecentIndexHasBeenFound = true;
      }
    }
    CurrentAnimationIndex = CandidateAnimationIndex;
  }

  Serial1.print("Starting animation #");
  Serial1.println(CurrentAnimationIndex);

  int SuggestedAnimationDuration = 0;
  switch(CurrentAnimationIndex) {
  case 0:
    SuggestedAnimationDuration = PlaneToCube.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    PlaneToCube.StartPlaneToCube();
    break;
  case 1:
    SuggestedAnimationDuration = PointToLine.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    PointToLine.StartPointToLine();
    break;
  case 2:
    SuggestedAnimationDuration = RandomPoints.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    RandomPoints.StartRandomPoints();
    break;
  case 3:
    SuggestedAnimationDuration = LinearFill.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    LinearFill.StartLinearFill();
    break;
  case 4:
    SuggestedAnimationDuration = FireworkRocket.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    FireworkRocket.StartFireworkRocket();
    break;
  case 5:
    SuggestedAnimationDuration = Tide.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Tide.StartTide();
    break;
  case 6:
    SuggestedAnimationDuration = Ball.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Ball.StartBall();
    break;
  case 7:
    SuggestedAnimationDuration = RandomFull.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    RandomFull.StartRandomFull();
    break;
  case 8:
    SuggestedAnimationDuration = StarrySky.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    StarrySky.StartStarrySky();
    break;
  case 9:
    SuggestedAnimationDuration = Fountain.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Fountain.StartFountain();
    break;
  case 10:
    SuggestedAnimationDuration = Waterfall.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Waterfall.StartWaterfall();
    break;
  case 11:
    SuggestedAnimationDuration = Windmill.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Windmill.StartWindmill();
    break;
  case 12:
    SuggestedAnimationDuration = Dash.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Dash.StartDash();
    break;
  case 13:
    SuggestedAnimationDuration = Spiral.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Spiral.StartSpiral();
    break;
  case 14:
    SuggestedAnimationDuration = StringFall.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    StringFall.StartStringFall();
    break;
  case 15:
    SuggestedAnimationDuration = FlopWall.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    FlopWall.StartFlopWall();
    break;
  case 16:
    SuggestedAnimationDuration = Pong.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Pong.StartPong();
    break;
  case 17:
    SuggestedAnimationDuration = MovingAxes.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    MovingAxes.StartMovingAxes();
    break;
  case 18:
    SuggestedAnimationDuration = ColorRegion.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    ColorRegion.StartColorRegion();
    break;
  case 19:
    SuggestedAnimationDuration = SlidingCube.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    SlidingCube.StartSlidingCube();
    break;
  case 20:
    SuggestedAnimationDuration = Iter.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Iter.StartIter();
    break;
  case 21:
    SuggestedAnimationDuration = Slosh.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Slosh.StartSlosh();
    break;
  case 22:
    SuggestedAnimationDuration = Pool.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Pool.StartPool();
    break;
  case 23:
    SuggestedAnimationDuration = Rotor.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Rotor.StartRotor();
    break;
  case 24:
    SuggestedAnimationDuration = Binary.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Binary.StartBinary();
    break;
  default:
    Serial1.println("Default case in MoveOnToNextAnimation()");
    SuggestedAnimationDuration = PlaneToCube.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    PlaneToCube.StartPlaneToCube();
    break;
  }
}

int LEDCube::RandomButDifferent(int ToBeAvoided, int LowEnd, int HighEnd) {
  int ReturnValue = LowEnd;
  int AllowedAttempts = 10;
  ReturnValue = random(LowEnd, HighEnd);
  while ((ReturnValue == ToBeAvoided) && (AllowedAttempts > 0)) {
    AllowedAttempts--;
    ReturnValue = random(LowEnd, HighEnd);
  }
  return ReturnValue;
}

int LEDCube::RandomPickOfTwo(int Candidate1, int Candidate2) {
  switch (random(0, 2)) {
  case 0:
    return Candidate1;
    break;
  case 1:
    return Candidate2;
    break;
  }
}

int LEDCube::RandomPickOfThree(int Candidate1, int Candidate2, int Candidate3) {
  switch (random(0, 3)) {
  case 0:
    return Candidate1;
    break;
  case 1:
    return Candidate2;
    break;
  case 2:
    return Candidate3;
    break;
  }
}

int LEDCube::RandomPickOfFour(int Candidate1, int Candidate2, int Candidate3, int Candidate4) {
  switch (random(0, 4)) {
  case 0:
    return Candidate1;
    break;
  case 1:
    return Candidate2;
    break;
  case 2:
    return Candidate3;
    break;
  case 3:
    return Candidate4;
    break;
  }
}

int LEDCube::RandomPickOfEight(int Candidate1, int Candidate2, int Candidate3, int Candidate4, int Candidate5, int Candidate6, int Candidate7, int Candidate8) {
  switch (random(0, 8)) {
  case 0:
    return Candidate1;
    break;
  case 1:
    return Candidate2;
    break;
  case 2:
    return Candidate3;
    break;
  case 3:
    return Candidate4;
    break;
  case 4:
    return Candidate5;
    break;
  case 5:
    return Candidate6;
    break;
  case 6:
    return Candidate7;
    break;
  case 7:
    return Candidate8;
    break;
  }
}

int LEDCube::NextIndex(int CurrentIndex, int NumberOfIndexes) {
  int TentativeReturnIndex = CurrentIndex + 1;
  if (TentativeReturnIndex >= NumberOfIndexes) {
    return 0;
  } else {
    return TentativeReturnIndex;
  }
}

int LEDCube::PreviousIndex(int CurrentIndex, int NumberOfIndexes) {
  int TentativeReturnIndex = CurrentIndex - 1;
  if (TentativeReturnIndex <= 0) {
    return NumberOfIndexes - 1;
  } else {
    return TentativeReturnIndex;
  }
}

int LEDCube::RandomColor() {
  return random(1, 8);
}

int LEDCube::CompositeColor(int Red, int Green, int Blue) {
  return ( Red << 8 ) + ( Green << 4 ) + Blue;
}

int LEDCube::RedPartOf(int CompositeColor) {
  return CompositeColor >> 8;
}

int LEDCube::GreenPartOf(int CompositeColor) {
  return ( CompositeColor >> 4 ) & 7;
}

int LEDCube::BluePartOf(int CompositeColor) {
  return CompositeColor & 7;
}

int LEDCube::NearbyColor(int Red, int Green, int Blue, int Distance) {
  int RedDelta;
  int NewRed;
  int GreenDelta;
  int NewGreen;
  int BlueDelta;
  int NewBlue;
  int IntensityTotal = Red + Green + Blue;
  if (IntensityTotal < 6) {
    // This is a relatively dim color... boost the dimmest
    if (Red < Green) {
      // Red is dimmer than Green
      if (Red < Blue) {
        // Red is dimmer than blue => red is the dimmest
        NewRed = min(7, Red + Distance);
        NewGreen = Green;
        NewBlue = Blue;
      } else {
        // Blue is dimmer than (or equal to) red => blue is effectively dimmest
        NewRed = Red;
        NewGreen = Green;
        NewBlue = min(7, Blue + Distance);
      }
    } else if (Red > Green) {
      // Red is brighter than green
      if (Green > Blue) {
        // Green is brighter than blue => blue is the dimmest
        NewRed = Red;
        NewGreen = Green;
        NewBlue = min(7, Blue + Distance);
      } else {
        // Green is dimmer than (or equal to) blue => green is effectively dimmest
        NewRed = Red;
        NewGreen = min(7, Green + Distance);
        NewBlue = Blue;
      }
    } else {
      // Red is equal brightness with green
      if (Blue < Red) {
        // Blue is dimmer than both red and green => blue is dimmest
        NewRed = Red;
        NewGreen = Green;
        NewBlue = min(7, Blue + Distance);
      } else {
        // Blue is either brighter than red = green or they're all the same....
        // Let's just pick green as the one to boost...
        NewRed = Red;
        NewGreen = min(7, Green + Distance);
        NewBlue = Blue;
      }
    }
  } else if (IntensityTotal > 15) {
    // This is a relatively bright color... decrease the brightest
    if (Red > Green) {
      // Red is brighter than green
      if (Red > Blue) {
        // Red is brighter than blue => red is brightest
        NewRed = max(0, Red - Distance);
        NewGreen = Green;
        NewBlue = Blue;
      } else {
        // Blue is brighter than (or equal to) red => blue is brightest
        NewRed = Red;
        NewGreen = Green;
        NewBlue = max(0, Blue - Distance);
      }
    } else if (Red < Green) {
      // Green is brighter than red
      if (Blue > Green) {
        // Blue is brighter than green => blue is the brightest
        NewRed = Red;
        NewGreen = Green;
        NewBlue = max(0, Blue - Distance);
      } else {
        // Green is brighter than (or equal to) blue = green is effectively brightest
        NewRed = Red;
        NewGreen = max(0, Green - Distance);
        NewBlue = Blue;
      }
    } else {
      // Red is equal brightness with green
      if (Blue > Red) {
        // Blue is brightest
        NewRed = Red;
        NewGreen = Green;
        NewBlue = max(0, Blue - Distance);
      } else {
        // Blue is either dimmer than red or they're all the same....
        // Let's pick red as the one to decrease
        NewRed = max(0, Red - Distance);
        NewGreen = Green;
        NewBlue = Blue;
      }
    }
  } else {
    // This is a middling-bright color... make random changes
    RedDelta = random(-Distance, Distance+1);
    NewRed = min(7, max(0, RedDelta));
    GreenDelta = random(-Distance, Distance+1);
    NewGreen = min(7, max(0, GreenDelta));
    BlueDelta = random(-Distance, Distance+1);
    NewBlue = min(7, max(0, BlueDelta));
  }
  // Don't return "LED is off" as a color...
  if ((NewRed == 0) && (NewGreen == 0) && (NewBlue == 0)) {
    switch(random(0, 3)) {
    case 0:
      NewRed = 1;
      break;
    case 1:
      NewGreen = 1;
      break;
    case 2:
      NewBlue = 1;
      break;
    }
  }
  return CompositeColor(NewRed, NewGreen, NewBlue);
}

int LEDCube::VeryCloseColor(int Red, int Green, int Blue) {
  int NewRed;
  int NewGreen;
  int NewBlue;
  switch(random(0, 3)) {
  case 0:
    // Vary the red
    if (Red > 3) {
      NewRed = Red - 1;
    } else {
      NewRed = Red + 1;
    }
    NewGreen = Green;
    NewBlue = Blue;
    break;
  case 1:
    // Vary the green
    if (Green > 3) {
      NewGreen = Green - 1;
    } else {
      NewGreen = Green + 1;
    }
    NewRed = Red;
    NewBlue = Blue;
    break;
  case 2:
    // Vary the blue
    if (Blue > 3) {
      NewBlue = Blue - 1;
    } else {
      NewBlue = Blue + 1;
    }
    NewRed = Red;
    NewGreen = Green;
    break;
  }
  return CompositeColor(NewRed, NewGreen, NewBlue);
}

int LEDCube::VeryDifferentColor(int Red, int Green, int Blue) {
  int NewRed;
  int NewGreen;
  int NewBlue;
  if (Red > 3) {
    NewRed = random(1, 3);
  } else {
    NewRed = random(6, 8);
  }
  if (Green > 3) {
    NewGreen = random(1, 3);
  } else {
    NewGreen = random(6, 8);
  }
  if (Blue > 3) {
    NewBlue = random(1, 3);
  } else {
    NewBlue = random(6, 8);
  }
  return CompositeColor(NewRed, NewGreen, NewBlue);
}

int LEDCube::SumOfThreeColors(int Color1, int Color2, int Color3) {
  return min(7, (Color1 + Color2 + Color3));
}

int LEDCube::DimmerColor(int Color) {
  return max(0, Color - 1);
}

int LEDCube::RandomSolidColor() {
  switch(random(0, 7)) {
  case 0:
    return CompositeColor(7, 0, 0);
    break;
  case 1:
    return CompositeColor(0, 7, 0);
    break;
  case 2:
    return CompositeColor(0, 0, 7);
    break;
  case 3:
    return CompositeColor(7, 7, 0);
    break;
  case 4:
    return CompositeColor(7, 0, 7);
    break;
  case 5:
    return CompositeColor(0, 7, 7);
    break;
  case 6:
    return CompositeColor(7, 7, 7);
    break;
  }
}


int LEDCube::RandomAxisPosition() {
  return random(0, 8);
}

int LEDCube::RandomDeltaPosition() {
  return RandomPickOfTwo(-1, 1);
}

int LEDCube::CompositePosition(int X, int Y, int Z) {
  return ( X << 8 ) + ( Y << 4 ) + Z;
}

// Find a randomly positioned LED that's already on or off
int LEDCube::RandomPositionWhereLEDIs(bool OnOrOff) {
  int AttemptCounter = 500;
  while (AttemptCounter > 0) {
    AttemptCounter--;
    int X = RandomAxisPosition();
    int Y = RandomAxisPosition();
    int Z = RandomAxisPosition();
    if (OnOrOff == ThisLEDIsOn(X, Y, Z)) {
      return CompositePosition(X, Y, Z);
    }
  }
  // Fail to center of the cube if too many unsuccessful tries
  return CompositePosition(4, 4, 4);
}

int LEDCube::RandomPositionWhereLEDIsOn() {
  return RandomPositionWhereLEDIs(true);
}

int LEDCube::RandomPositionWhereLEDIsOff() {
  return RandomPositionWhereLEDIs(false);
}

int LEDCube::NearbyCoordinate(int Coordinate, int Distance) {
  int NewCoordinate = Coordinate + random(-Distance, Distance + 1);
  if (NewCoordinate < 0) {
    NewCoordinate = 0;
  }
  if (NewCoordinate > 7) {
    NewCoordinate = 7;
  }
  return NewCoordinate;
}

int LEDCube::XPartOf(int CompositePosition) {
  return CompositePosition >> 8;
}

int LEDCube::YPartOf(int CompositePosition) {
  return (CompositePosition >> 4) & 7;
}

int LEDCube::ZPartOf(int CompositePosition) {
  return CompositePosition & 7;
}

int LEDCube::CenterBias(int Position) {
  if (Position > 3) {
    return -1;
  } else {
    return 1;
  }
}

void LEDCube::ClearImage() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      for (int z = 0; z < 8; z++) {
        SetLEDColor(x, y, z, 0, 0, 0);
      }
    }
  }
}

void LEDCube::FillLayer(int Layer, int Red, int Green, int Blue) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      SetLEDColor(x, y, Layer, Red, Green, Blue);
    }
  }
}

bool LEDCube::ThisLEDIsOn(int X, int Y, int Z) {
  if (LEDIsOn[X][Y][Z] == 1) {
    return true;
  }
  return false;
}

void LEDCube::SetLEDColor(int XLeftToRight, int YFrontToBack, int ZBottomToTop, int Red, int Green, int Blue) {
  int Xindex = 0;
  int Yindex = 0;
  int Zindex = 0;
  int RedIntensity = 0;
  int GreenIntensity = 0;
  int BlueIntensity = 0;
  int RedByteIndex = 0;
  int GreenByteIndex = 0;
  int BlueByteIndex = 0;
  int ByteBitMask = 0;
  int ColorBitMask = 0;
  bool RedIntensityBits[ColorDepth];
  bool GreenIntensityBits[ColorDepth];
  bool BlueIntensityBits[ColorDepth];
  int LEDState;


  Xindex = max(0, min(7, XLeftToRight));
  Yindex = max(0, min(7, YFrontToBack));
  Zindex = max(0, min(7, ZBottomToTop));
  RedIntensity = max(0, min(7, Red));
  GreenIntensity = max(0, min(7, Green));
  BlueIntensity = max(0, min(7, Blue));

  // Update the LEDIsOn array
  if ((RedIntensity == 0) && (GreenIntensity == 0) && (BlueIntensity == 0)){
    LEDState = 0;
  } else {
    LEDState = 1;
  }
  LEDIsOn[Xindex][Yindex][Zindex] = LEDState;

  // Get the (X coordinate's) shift register byte index for each color
  RedByteIndex = RedXCoordinateToShiftRegisterByteIndex(Xindex);
  GreenByteIndex = GreenXCoordinateToShiftRegisterByteIndex(Xindex);
  BlueByteIndex = BlueXCoordinateToShiftRegisterByteIndex(Xindex);
  // Get the (Y coordinate's) bit mask
  ByteBitMask = YCoordinateToBitMask(Yindex);
  // Figure the color intensity bits for each color
  ColorBitMask = 1;
  for (int c = 0; c < ColorDepth; c++) {
    RedIntensityBits[c] = (RedIntensity & ColorBitMask) > 0;
    GreenIntensityBits[c] = (GreenIntensity & ColorBitMask) > 0;
    BlueIntensityBits[c] = (BlueIntensity & ColorBitMask) > 0;
    ColorBitMask = ColorBitMask << 1;
    }
  // Make the needed changes to the data array
  for (int c = 0; c < ColorDepth; c++) {
    if (RedIntensityBits[c]) {
      Image[c][Zindex][RedByteIndex] = Image[c][Zindex][RedByteIndex] | ByteBitMask;
    } else {
      Image[c][Zindex][RedByteIndex] = Image[c][Zindex][RedByteIndex] & ~ByteBitMask;
    }
    if (GreenIntensityBits[c]) {
      Image[c][Zindex][GreenByteIndex] = Image[c][Zindex][GreenByteIndex] | ByteBitMask;
    } else {
      Image[c][Zindex][GreenByteIndex] = Image[c][Zindex][GreenByteIndex] & ~ByteBitMask;
    }
    if (BlueIntensityBits[c]) {
      Image[c][Zindex][BlueByteIndex] = Image[c][Zindex][BlueByteIndex] | ByteBitMask;
    } else {
      Image[c][Zindex][BlueByteIndex] = Image[c][Zindex][BlueByteIndex] & ~ByteBitMask;
    }
  }
}

int LEDCube::GetLEDColor(int XLeftToRight, int YFrontToBack, int ZBottomToTop) {
  int Xindex = 0;
  int Yindex = 0;
  int Zindex = 0;
  int RedIntensity = 0;
  int GreenIntensity = 0;
  int BlueIntensity = 0;
  int RedByteIndex = 0;
  int GreenByteIndex = 0;
  int BlueByteIndex = 0;
  int ByteBitMask = 0;
  int ColorBitMask = 0;
  bool RedIntensityBits[ColorDepth];
  bool GreenIntensityBits[ColorDepth];
  bool BlueIntensityBits[ColorDepth];
  int IntensityBitIntegerEquivalent = 0;
  if (XLeftToRight < 0 || XLeftToRight > 7) {
    Xindex = 0;
  } else {
    Xindex = XLeftToRight;
  }
  if (YFrontToBack < 0 || YFrontToBack > 7) {
    Yindex = 0;
  } else {
    Yindex = YFrontToBack;
  }
  if (ZBottomToTop < 0 || ZBottomToTop > 7) {
    Zindex = 0;
  } else {
    Zindex = ZBottomToTop;
  }
  // Get the (X coordinate's) shift register byte index for each color
  RedByteIndex = RedXCoordinateToShiftRegisterByteIndex(Xindex);
  GreenByteIndex = GreenXCoordinateToShiftRegisterByteIndex(Xindex);
  BlueByteIndex = BlueXCoordinateToShiftRegisterByteIndex(Xindex);
  // Get the (Y coordinate's) bit mask
  ByteBitMask = YCoordinateToBitMask(Yindex);
  // Read the color data in the given position
  ColorBitMask = 1;
  // First collect the individual color intensity bits
  for (int c = 0; c < ColorDepth; c++) {
    RedIntensityBits[c] = (Image[c][Zindex][RedByteIndex] & ByteBitMask) > 0;
    GreenIntensityBits[c] = (Image[c][Zindex][GreenByteIndex] & ByteBitMask) > 0;
    BlueIntensityBits[c] = (Image[c][Zindex][BlueByteIndex] & ByteBitMask) > 0;
    ColorBitMask = ColorBitMask << 1;
    }
  // Assemble the color bits into integer color intensity values
  IntensityBitIntegerEquivalent = 1;
  for (int c = 0; c < ColorDepth; c++) {
    if (RedIntensityBits[c]) {
      RedIntensity += IntensityBitIntegerEquivalent;
    }
    if (GreenIntensityBits[c]) {
      GreenIntensity += IntensityBitIntegerEquivalent;
    }
    if (BlueIntensityBits[c]) {
      BlueIntensity += IntensityBitIntegerEquivalent;
    }
    IntensityBitIntegerEquivalent = IntensityBitIntegerEquivalent << 1;
  }
}

void LEDCube::RenderImageToPhysicalCube() {
  // Loop through the color depths
  for (int ColorIntensityPassCounter = 0; ColorIntensityPassCounter < ColorIntensityPassCount; ColorIntensityPassCounter++) {
    int CurrentColorIntensityIndex = ColorIntensityIndexSelector[ColorIntensityPassCounter];
    // Loop through each Z-Axis level:
    for (int z = 0; z < Height; z++) {
      ClearCurrentLayer();
      SwitchToLayer(z);

      // Shift the current level's data into the shift registers
      digitalWrite(LE, LOW);
      for (int x = 0; x < ShiftRegisterBytes; x++) {
        SPI.transfer(Image[CurrentColorIntensityIndex][z][x]);
      } // end for (int x
      digitalWrite(LE, HIGH);
      
    } // end for (int z = 0...
  } // end for (int ColorIntensityPassCounter...
}

// Function to enable the anode drive for one of the 8 vertical layers:
void LEDCube::SwitchToLayer(int z) {
  if (z == 0) {
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
  } else if (z == 1) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
  } else if (z == 2) {
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
  } else if (z == 3) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
  } else if (z == 4) {
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
  } else if (z == 5) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
  } else if (z == 6) {
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
  } else if (z == 7) {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
  }
}

// Clear entire current layer:
void LEDCube::ClearCurrentLayer() {
  digitalWrite(LE, LOW);
  for (int i = 0; i < ShiftRegisterBytes; i++)
    SPI.transfer(0);
  digitalWrite(LE, HIGH);
}

// Convert X coordinate to RED segment's shift register byte index
int LEDCube::RedXCoordinateToShiftRegisterByteIndex(int X) {
  switch(X) {
    case 0:
      return 23;
      break;
    case 1:
      return 22;
      break;
    case 2:
      return 17;
      break;
    case 3:
      return 16;
      break;
    case 4:
      return 11;
      break;
    case 5:
      return 10;
      break;
    case 6:
      return 5;
      break;
    case 7:
      return 4;
      break;
  }
}

// Convert X coordinate to GREEN segment's shift register byte index
int LEDCube::GreenXCoordinateToShiftRegisterByteIndex(int X) {
  switch(X) {
    case 0:
      return 19;
      break;
    case 1:
      return 18;
      break;
    case 2:
      return 13;
      break;
    case 3:
      return 12;
      break;
    case 4:
      return 7;
      break;
    case 5:
      return 6;
      break;
    case 6:
      return 1;
      break;
    case 7:
      return 0;
      break;
  }
}

// Convert X coordinate to BLUE segment's shift register byte index
int LEDCube::BlueXCoordinateToShiftRegisterByteIndex(int X) {
  switch(X) {
    case 0:
      return 21;
      break;
    case 1:
      return 20;
      break;
    case 2:
      return 15;
      break;
    case 3:
      return 14;
      break;
    case 4:
      return 9;
      break;
    case 5:
      return 8;
      break;
    case 6:
      return 3;
      break;
    case 7:
      return 2;
      break;
  }
}

// Convert Y coordinate to bit mask
int LEDCube::YCoordinateToBitMask(int Y) {
  switch(Y) {
    case 0:
      return 128;
      break;
    case 1:
      return 64;
      break;
    case 2:
      return 32;
      break;
    case 3:
      return 16;
      break;
    case 4:
      return 8;
      break;
    case 5:
      return 4;
      break;
    case 6:
      return 2;
      break;
    case 7:
      return 1;
      break;
  }
}


