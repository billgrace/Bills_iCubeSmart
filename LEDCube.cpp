// LEDCube.cpp
/*
This class has two main purposes:
1 - Maintain a data array representing the physical LED cube and render that array
      to the physical cube. The array is laid out in a human-sensible way such as
      X value from 0 to 7 means leftmost to rightmost, Y 0..7 means bottom to top, etc.
2 - All kinds of utility routines are located in this class so they'll be available
      to all the animation classes. This saves a lot of duplicate code in the long run.
*/
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
#include "LEDSHape.h"
#include "LEDCombo1.h"
#include "LEDCombo2.h"
#include "LEDRandomFill.h"
#include "LEDSonar.h"
#include "LEDRadar.h"
#include "LEDLineFill.h"
#include "LEDBarGraph.h"
#include "LEDMerryGoRound.h"
#include "LEDMarathon.h"
#include "LEDCombo3.h"
#include "LEDCombo4.h"
#include "LEDCombo5.h"
#include "LEDCombo6.h"
#include "LEDCombo7.h"
#include "LEDCorner.h"
#include "LEDJumpRope.h"
#include "LEDBasketBall.h"
#include "LEDLoopFill.h"
#include "LEDLightning.h"
#include "LEDChase.h"
#include "LEDRainbow.h"
#include "LEDCombo8.h"
#include "LEDCombo9.h"
#include "LEDColumns.h"
#include "LEDWorms.h"
#include "LEDSprinkler.h"
#include "LEDCombo10.h"
#include "LEDCombo11.h"
#include "LEDSheets.h"
#include "LEDCylinder.h"
#include "LEDPinWheel.h"
#include "LEDCloud.h"
#include "LEDWireCube.h"
#include "LEDFace.h"

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
extern LEDShape Shape;
extern LEDCombo1 Combo1;
extern LEDCombo2 Combo2;
extern LEDRandomFill RandomFill;
extern LEDSonar Sonar;
extern LEDRadar Radar;
extern LEDLineFill LineFill;
extern LEDBarGraph BarGraph;
extern LEDMerryGoRound MerryGoRound;
extern LEDMarathon Marathon;
extern LEDCombo3 Combo3;
extern LEDCombo4 Combo4;
extern LEDCombo5 Combo5;
extern LEDCombo6 Combo6;
extern LEDCombo7 Combo7;
extern LEDCorner Corner;
extern LEDJumpRope JumpRope;
extern LEDBasketBall BasketBall;
extern LEDLoopFill LoopFill;
extern LEDLightning Lightning;
extern LEDChase Chase;
extern LEDRainbow Rainbow;
extern LEDCombo8 Combo8;
extern LEDCombo9 Combo9;
extern LEDColumns Columns;
extern LEDWorms Worms;
extern LEDSprinkler Sprinkler;
extern LEDCombo10 Combo10;
extern LEDCombo11 Combo11;
extern LEDSheets Sheets;
extern LEDCylinder Cylinder;
extern LEDPinWheel PinWheel;
extern LEDCloud Cloud;
extern LEDWireCube WireCube;
extern LEDFace Face;

// The class constructor here sets up the processor pins controlling the cube's LEDs
LEDCube::LEDCube() {
  // "TestMode" is a development tool allowing a particular animation to be run over
  //  and over without having to wait for it to be picked by the normal random process.
  // "TestAnimationIndex" is the animation to be repeated
  // "TestAlternateIndex" is an animation to be run between repeats of the animation
  //   under test. This helps make visible when the test animation starts and stops.
  //   The alternate index defaults to 1 - the "PointToLine" animation which is easy
  //   to recognize and finishes fairly quickly. I don't think I've ever felt a need
  //   to change the alternate to some other animation but the serial protocol DOES
  //   include a function to do that. 
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

// These routines are development helps. The "GlobalBoolean" and "GlobalInteger"
//  routines allow animations being developed to use variables which can be set
//  manually via the serial protocol.
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


// The following two routines provide a way for each animation to decide when it
//  should quit and allow another animation to begin. When an animation is started,
//  it provides the number of "cycles" it should be allowed. As the animation is in
//  operation, it increments the cycle counter whenever it wants and the central code
//  which starts new animations knows it's time to move to a new animation when the
//  cycle counter exceeds the initial number of cycles it was given.
void LEDCube::SetAnimationDurationInCycles(int Cycles) {
  AnimationDurationInCycles = Cycles;
  AnimationDurationCycleCounter = 0;
}

void LEDCube::IncrementAnimationDurationCycleCount() {
  AnimationDurationCycleCounter++;
}


// Each animation calls this routine when it is started to tell the central code
//  how often it should call the animation's "Step" routine.
void LEDCube::SetAnimationStepSpeedPeriodTo(int Period) {
  AnimationStepSpeedPeriod = Period;
  AnimationStepSpeedCounter = 0;
}

// (this is another way an animation can specify how often it should be Step'd
void LEDCube::SetRandomizedAnimationStepSpeedPeriod(int Period, int RandRange) {
  int MinimumRandomParameter = max(Period - RandRange, 2);
  AnimationStepSpeedPeriod = random(MinimumRandomParameter, Period + RandRange);
  AnimationStepSpeedCounter = 0;
}


// This routine is called every millisecond by the Timer1 interrupt service routine.
// It checks a few things each time it's called:
//  1) has the animation been paused by the serial protocol? if so do nothing
//  2) is it time to start up a new animation? if so call the routine to do that
//  3) is it time to call the current animation's "Step" routine? if so do that
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
      case 24:
        Binary.StepBinary();
        break;
      case 25:
        Shape.StepShape();
        break;
      case 26:
        Combo1.StepCombo1();
        break;
      case 27:
        Combo2.StepCombo2();
        break;
      case 28:
        RandomFill.StepRandomFill();
        break;
      case 29:
        Sonar.StepSonar();
        break;
      case 30:
        Radar.StepRadar();
        break;
      case 31:
        LineFill.StepLineFill();
        break;
      case 32:
        BarGraph.StepBarGraph();
        break;
      case 33:
        MerryGoRound.StepMerryGoRound();
        break;
      case 34:
        Marathon.StepMarathon();
        break;
      case 35:
        Combo3.StepCombo3();
        break;
      case 36:
        Combo4.StepCombo4();
        break;
      case 37:
        Combo5.StepCombo5();
        break;
      case 38:
        Combo6.StepCombo6();
        break;
      case 39:
        Combo7.StepCombo7();
        break;
      case 40:
        Corner.StepCorner();
        break;
      case 41:
        JumpRope.StepJumpRope();
        break;
      case 42:
        BasketBall.StepBasketBall();
        break;
      case 43:
        LoopFill.StepLoopFill();
        break;
      case 44:
        Lightning.StepLightning();
        break;
      case 45:
        Chase.StepChase();
        break;
      case 46:
        Rainbow.StepRainbow();
        break;
      case 47:
        Combo8.StepCombo8();
        break;
      case 48:
        Combo9.StepCombo9();
        break;
      case 49:
        Columns.StepColumns();
        break;
      case 50:
        Worms.StepWorms();
        break;
      case 51:
        Sprinkler.StepSprinkler();
        break;
      case 52:
        Combo10.StepCombo10();
        break;
      case 53:
        Combo11.StepCombo11();
        break;
      case 54:
        Sheets.StepSheets();
        break;
      case 55:
        Cylinder.StepCylinder();
        break;
      case 56:
        PinWheel.StepPinWheel();
        break;
      case 57:
        Cloud.StepCloud();
        break;
      case 58:
        WireCube.StepWireCube();
        break;
      case 59:
        Face.StepFace();
        break;
      default:
        Serial1.print("Default case in AnimationStepThrottle(): ");
        Serial1.println(CurrentAnimationIndex);
        break;
      }
    }
  }
}


// This routine is called when it's time to start up a new animation. It keeps track
//  of the animations that have recently run so it can choose one which hasn't been
//  run recently.
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
  case 25:
    SuggestedAnimationDuration = Shape.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Shape.StartShape();
    break;
  case 26:
    SuggestedAnimationDuration = Combo1.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo1.StartCombo1();
    break;
  case 27:
    SuggestedAnimationDuration = Combo2.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo2.StartCombo2();
    break;
  case 28:
    SuggestedAnimationDuration = RandomFill.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    RandomFill.StartRandomFill();
    break;
  case 29:
    SuggestedAnimationDuration = Sonar.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Sonar.StartSonar();
    break;
  case 30:
    SuggestedAnimationDuration = Radar.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Radar.StartRadar();
    break;
  case 31:
    SuggestedAnimationDuration = LineFill.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    LineFill.StartLineFill();
    break;
  case 32:
    SuggestedAnimationDuration = BarGraph.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    BarGraph.StartBarGraph();
    break;
  case 33:
    SuggestedAnimationDuration = MerryGoRound.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    MerryGoRound.StartMerryGoRound();
    break;
  case 34:
    SuggestedAnimationDuration = Marathon.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Marathon.StartMarathon();
    break;
  case 35:
    SuggestedAnimationDuration = Combo3.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo3.StartCombo3();
    break;
  case 36:
    SuggestedAnimationDuration = Combo4.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo4.StartCombo4();
    break;
  case 37:
    SuggestedAnimationDuration = Combo5.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo5.StartCombo5();
    break;
  case 38:
    SuggestedAnimationDuration = Combo6.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo6.StartCombo6();
    break;
  case 39:
    SuggestedAnimationDuration = Combo7.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo7.StartCombo7();
    break;
  case 40:
    SuggestedAnimationDuration = Corner.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Corner.StartCorner();
    break;
  case 41:
    SuggestedAnimationDuration = JumpRope.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    JumpRope.StartJumpRope();
    break;
  case 42:
    SuggestedAnimationDuration = BasketBall.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    BasketBall.StartBasketBall();
    break;
  case 43:
    SuggestedAnimationDuration = LoopFill.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    LoopFill.StartLoopFill();
    break;
  case 44:
    SuggestedAnimationDuration = Lightning.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Lightning.StartLightning();
    break;
  case 45:
    SuggestedAnimationDuration = Chase.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Chase.StartChase();
    break;
  case 46:
    SuggestedAnimationDuration = Rainbow.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Rainbow.StartRainbow();
    break;
  case 47:
    SuggestedAnimationDuration = Combo8.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo8.StartCombo8();
    break;
  case 48:
    SuggestedAnimationDuration = Combo9.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo9.StartCombo9();
    break;
  case 49:
    SuggestedAnimationDuration = Columns.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Columns.StartColumns();
    break;
  case 50:
    SuggestedAnimationDuration = Worms.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Worms.StartWorms();
    break;
  case 51:
    SuggestedAnimationDuration = Sprinkler.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Sprinkler.StartSprinkler();
    break;
  case 52:
    SuggestedAnimationDuration = Combo10.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo10.StartCombo10();
    break;
  case 53:
    SuggestedAnimationDuration = Combo11.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Combo11.StartCombo11();
    break;
  case 54:
    SuggestedAnimationDuration = Sheets.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Sheets.StartSheets();
    break;
  case 55:
    SuggestedAnimationDuration = Cylinder.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Cylinder.StartCylinder();
    break;
  case 56:
    SuggestedAnimationDuration = PinWheel.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    PinWheel.StartPinWheel();
    break;
  case 57:
    SuggestedAnimationDuration = Cloud.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Cloud.StartCloud();
    break;
  case 58:
    SuggestedAnimationDuration = WireCube.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    WireCube.StartWireCube();
    break;
  case 59:
    SuggestedAnimationDuration = Face.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    Face.StartFace();
    break;
  default:
    Serial1.println("Default case in MoveOnToNextAnimation()");
    SuggestedAnimationDuration = PlaneToCube.SuggestedNumberOfAnimationCycles();
    SetAnimationDurationInCycles(SuggestedAnimationDuration);
    PlaneToCube.StartPlaneToCube();
    break;
  }
}


// ********************* Lots of handy utility routines ***********************
// Same as Arduino's standard random number routine but WON'T allow a particular value
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

// Randomly pick between 2 candidate numbers
int LEDCube::RandomPickOfTwo(int Candidate1, int Candidate2) {
  int ReturnValue = 0;
  switch (random(0, 2)) {
  case 0:
    ReturnValue = Candidate1;
    break;
  case 1:
    ReturnValue = Candidate2;
    break;
  }
  return ReturnValue;
}

// Randomly pick between 3 candidate numbers
int LEDCube::RandomPickOfThree(int Candidate1, int Candidate2, int Candidate3) {
  int ReturnValue = 0;
  switch (random(0, 3)) {
  case 0:
    ReturnValue = Candidate1;
    break;
  case 1:
    ReturnValue = Candidate2;
    break;
  case 2:
    ReturnValue = Candidate3;
    break;
  }
  return ReturnValue;
}

// Randomly pick between 4 candidate numbers
int LEDCube::RandomPickOfFour(int Candidate1, int Candidate2, int Candidate3, int Candidate4) {
  int ReturnValue = 0;
  switch (random(0, 4)) {
  case 0:
    ReturnValue = Candidate1;
    break;
  case 1:
    ReturnValue = Candidate2;
    break;
  case 2:
    ReturnValue = Candidate3;
    break;
  case 3:
    ReturnValue = Candidate4;
    break;
  }
  return ReturnValue;
}

// Randomly pick between 8 candidate numbers
int LEDCube::RandomPickOfEight(int Candidate1, int Candidate2, int Candidate3, int Candidate4, int Candidate5, int Candidate6, int Candidate7, int Candidate8) {
  int ReturnValue = 0;
  switch (random(0, 8)) {
  case 0:
    ReturnValue = Candidate1;
    break;
  case 1:
    ReturnValue = Candidate2;
    break;
  case 2:
    ReturnValue = Candidate3;
    break;
  case 3:
    ReturnValue = Candidate4;
    break;
  case 4:
    ReturnValue = Candidate5;
    break;
  case 5:
    ReturnValue = Candidate6;
    break;
  case 6:
    ReturnValue = Candidate7;
    break;
  case 7:
    ReturnValue = Candidate8;
    break;
  }
  return ReturnValue;
}

// Randomly pick between 16 candidate numbers
int LEDCube::RandomPickOfSixteen(int Candidate1, int Candidate2, int Candidate3, int Candidate4, int Candidate5, int Candidate6, int Candidate7, int Candidate8, int Candidate9, int Candidate10, int Candidate11, int Candidate12, int Candidate13, int Candidate14, int Candidate15, int Candidate16) {
  int ReturnValue = 0;
  switch (random(0, 16)) {
  case 0:
    ReturnValue = Candidate1;
    break;
  case 1:
    ReturnValue = Candidate2;
    break;
  case 2:
    ReturnValue = Candidate3;
    break;
  case 3:
    ReturnValue = Candidate4;
    break;
  case 4:
    ReturnValue = Candidate5;
    break;
  case 5:
    ReturnValue = Candidate6;
    break;
  case 6:
    ReturnValue = Candidate7;
    break;
  case 7:
    ReturnValue = Candidate8;
    break;
  case 8:
    ReturnValue = Candidate9;
    break;
  case 9:
    ReturnValue = Candidate10;
    break;
  case 10:
    ReturnValue = Candidate11;
    break;
  case 11:
    ReturnValue = Candidate12;
    break;
  case 12:
    ReturnValue = Candidate13;
    break;
  case 13:
    ReturnValue = Candidate14;
    break;
  case 14:
    ReturnValue = Candidate15;
    break;
  case 15:
    ReturnValue = Candidate16;
    break;
  }
  return ReturnValue;
}

// Return the next in a series of zero-based integers
int LEDCube::NextIndex(int CurrentIndex, int NumberOfIndexes) {
  int ReturnValue = 0;
  int TentativeReturnIndex = CurrentIndex + 1;
  if (TentativeReturnIndex >= NumberOfIndexes) {
    ReturnValue = 0;
  } else {
    ReturnValue = TentativeReturnIndex;
  }
  return ReturnValue;
}

// Return the previous in a series of zero-based integers
int LEDCube::PreviousIndex(int CurrentIndex, int NumberOfIndexes) {
  int ReturnValue = 0;
  int TentativeReturnIndex = CurrentIndex - 1;
  if (TentativeReturnIndex <= 0) {
    ReturnValue = NumberOfIndexes - 1;
  } else {
    ReturnValue = TentativeReturnIndex;
  }
  return ReturnValue;
}

// Return a random color (0..7)
int LEDCube::RandomColor() {
  return random(1, 8);
}

// Return a single integer that combines given red, green and blue parts
int LEDCube::CompositeColor(int Red, int Green, int Blue) {
  return ( Red << 8 ) + ( Green << 4 ) + Blue;
}

// Break down a composite color into separate red, green and blue parts
int LEDCube::RedPartOf(int CompositeColor) {
  return CompositeColor >> 8;
}

int LEDCube::GreenPartOf(int CompositeColor) {
  return ( CompositeColor >> 4 ) & 7;
}

int LEDCube::BluePartOf(int CompositeColor) {
  return CompositeColor & 7;
}

// Return a (composite) color which is somewhat "close" to the given RGB
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

// Return a (composite) color which is very close to the given RGB
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

// return a (composite) color which is very different from the given RGB
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

// Return a sum of three (R or G or B) colors limited to 7 which is the max a color can be
int LEDCube::SumOfThreeColors(int Color1, int Color2, int Color3) {
  return min(7, (Color1 + Color2 + Color3));
}

// Decriment the given color but don't allow it to go below 0
int LEDCube::DimmerColor(int Color) {
  return max(0, Color - 1);
}

// Return a random (composite) color which is one of:
// Red
// Green
// Blue
// Magenta
// Cyan
// Yellow
// White
// ... i.e. a "solid" color where each of R and G and B are either all on or off
int LEDCube::RandomSolidColor() {
  int ReturnValue = 0;
  switch(random(0, 7)) {
  case 0:
    ReturnValue = CompositeColor(7, 0, 0);
    break;
  case 1:
    ReturnValue = CompositeColor(0, 7, 0);
    break;
  case 2:
    ReturnValue = CompositeColor(0, 0, 7);
    break;
  case 3:
    ReturnValue = CompositeColor(7, 7, 0);
    break;
  case 4:
    ReturnValue = CompositeColor(7, 0, 7);
    break;
  case 5:
    ReturnValue = CompositeColor(0, 7, 7);
    break;
  case 6:
    ReturnValue = CompositeColor(7, 7, 7);
    break;
  }
  return ReturnValue;
}

// Return a random position 0..7
int LEDCube::RandomAxisPosition() {
  return random(0, 8);
}

// Return a random position delta: -1 or 1
int LEDCube::RandomDeltaPosition() {
  return RandomPickOfTwo(-1, 1);
}

// Return a composite integer containing all three axis positions
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
  // Fail to come up with a requested position
  return -1;
}

// Return a (composite) position which is within some distance of the given position
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

// Return the X, Y and Z parts of a composite position
int LEDCube::XPartOf(int CompositePosition) {
  return CompositePosition >> 8;
}

int LEDCube::YPartOf(int CompositePosition) {
  return (CompositePosition >> 4) & 7;
}

int LEDCube::ZPartOf(int CompositePosition) {
  return CompositePosition & 7;
}

// Given an axis position, return the delta which will move that position away
//  from the LED cube sides and towards the LED cube center
int LEDCube::CenterBias(int Position) {
  int ReturnValue = 0;
  if (Position > 3) {
    ReturnValue = -1;
  } else {
    ReturnValue = 1;
  }
  return ReturnValue;
}

// Turn off all the LEDs in the cube
void LEDCube::ClearImage() {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      for (int z = 0; z < 8; z++) {
        SetLEDColor(x, y, z, 0, 0, 0);
      }
    }
  }
}

// Given a Z-axis value ("Layer"), fill that LED cube layer with a particular color
void LEDCube::FillLayer(int Layer, int Red, int Green, int Blue) {
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      SetLEDColor(x, y, Layer, Red, Green, Blue);
    }
  }
}

// Return true if a particular LED is on (any color), false if it's off
bool LEDCube::ThisLEDIsOn(int X, int Y, int Z) {
  bool ReturnValue = false;
  if (LEDIsOn[X][Y][Z] == 1) {
    ReturnValue = true;
  } else {
    ReturnValue = false;
  }
  return ReturnValue;
}

// Set the LED at the given location to the given color.
//   Also update the secondary array that tracks whether each LED is
//    on or off regardless of color.
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

// Given an LED position, return the current (composite) color of that LED
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
  return CompositeColor(RedIntensity, GreenIntensity, BlueIntensity);
}

// This routine copies the LED color data array out to the physical shift registers and
//  latch in such a way that the desired colors appear to the eye of anyone looking at
//  the cube.
// It's a bit convoluted and depends on the relative slowness of the human eye.
// This routine runs two cycles and runs them both so fast that most people won't
//  see any flicker in the LED cube.
// The simple cycle consists of lighting up LEDs on one layer at a time. It happens so
//  fast that all the layers *appear* to be lit up but actually, only one layer at a 
//  time actually has its LEDs turned on. This cycle is driven by the for (int z...)
//  loop which sends bits through the shift registers to light up (or not) each LED
//  color (cathode) on a layer, turns on the common anodes for that layer then moves
//  on to the next layer. This makes the LED cube *appear* to be lit up from top to
//  bottom when in reality it's being lit up one layer at a time.
// The more subtle cycle is driven by the outermost loop (for ColorIntensityPassCounter).
//  This loop runs through 7 steps to implement the brightness of the colors.
//  Each color (Red, Green, Blue) in each LED is assigned three bits to allow color
//  intensity to range from 0 through 7. Each step of this cycle includes the entire
//  set of all 8 layers *BUT* sends different color bits to the LED cathodes through
//  the shift registers. Since the color brightness of each LED segment is controlled
//  via three bits, there's one bit that counts as 4, one that counts as 2 and one
//  that counts as 1 (standard binary encoding of 0 through 7). During the 7 steps of
//  this color-intensity cycle the "4" bit is sent out 4 times, the "2" bit is sent
//  out twice and the "1" bit is sent once. This causes the LEDs to appear to be
//  brightest when all three bits are on and dimmest when only the "1" bit is on.
void LEDCube::RenderImageToPhysicalCube() {
  // Loop through the color depths
  for (int ColorIntensityPassCounter = 0; ColorIntensityPassCounter < ColorIntensityPassCount; ColorIntensityPassCounter++) {
    int CurrentColorIntensityIndex = ColorIntensityIndexSelector[ColorIntensityPassCounter];
    // Loop through each Z-Axis level:
    for (int z = 0; z < CubeHeight; z++) {
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

// Function to enable the anode drive which lights up one of the 8 vertical layers:
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

// Paint a rainbow into the cube
void LEDCube::PaintRainbow() {
  for (int C = 0; C < ColorDepth; C++) {
    for (int H = 0; H < 8; H++) {
      for (int S = 0; S < 24; S++) {
        Image[C][H][S] = RainbowImage[C][H][S];
      }
    }
  }
}

// Convert X coordinate to RED segment's shift register byte index
int LEDCube::RedXCoordinateToShiftRegisterByteIndex(int X) {
  int ReturnValue = 0;
  switch(X) {
    case 0:
      ReturnValue = 23;
      break;
    case 1:
      ReturnValue = 22;
      break;
    case 2:
      ReturnValue = 17;
      break;
    case 3:
      ReturnValue = 16;
      break;
    case 4:
      ReturnValue = 11;
      break;
    case 5:
      ReturnValue = 10;
      break;
    case 6:
      ReturnValue = 5;
      break;
    case 7:
      ReturnValue = 4;
      break;
  }
  return ReturnValue;
}

// Convert X coordinate to GREEN segment's shift register byte index
int LEDCube::GreenXCoordinateToShiftRegisterByteIndex(int X) {
  int ReturnValue = 0;
  switch(X) {
    case 0:
      ReturnValue = 19;
      break;
    case 1:
      ReturnValue = 18;
      break;
    case 2:
      ReturnValue = 13;
      break;
    case 3:
      ReturnValue = 12;
      break;
    case 4:
      ReturnValue = 7;
      break;
    case 5:
      ReturnValue = 6;
      break;
    case 6:
      ReturnValue = 1;
      break;
    case 7:
      ReturnValue = 0;
      break;
  }
  return ReturnValue;
}

// Convert X coordinate to BLUE segment's shift register byte index
int LEDCube::BlueXCoordinateToShiftRegisterByteIndex(int X) {
  int ReturnValue = 0;
  switch(X) {
    case 0:
      ReturnValue = 21;
      break;
    case 1:
      ReturnValue = 20;
      break;
    case 2:
      ReturnValue = 15;
      break;
    case 3:
      ReturnValue = 14;
      break;
    case 4:
      ReturnValue = 9;
      break;
    case 5:
      ReturnValue = 8;
      break;
    case 6:
      ReturnValue = 3;
      break;
    case 7:
      ReturnValue = 2;
      break;
  }
  return ReturnValue;
}

// Convert Y coordinate to bit mask
int LEDCube::YCoordinateToBitMask(int Y) {
  int ReturnValue = 0;
  switch(Y) {
    case 0:
      ReturnValue = 128;
      break;
    case 1:
      ReturnValue = 64;
      break;
    case 2:
      ReturnValue = 32;
      break;
    case 3:
      ReturnValue = 16;
      break;
    case 4:
      ReturnValue = 8;
      break;
    case 5:
      ReturnValue = 4;
      break;
    case 6:
      ReturnValue = 2;
      break;
    case 7:
      ReturnValue = 1;
      break;
  }
  return ReturnValue;
}


