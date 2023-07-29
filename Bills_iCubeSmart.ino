// Bill_s_iCubeSmart

// Arduino.h brings in many fundamental Arduino resources
#include <Arduino.h>

// SPI.h brings in serial communications
#include <SPI.h>

// LEDCube provides my own set of functions dealing with the iSmart LED cube 
#include "LEDCube.h"

// LEDMove provides motion functions for use by animations
#include "LEDMove.h"

// Put up a square, extend it into a cube, then back to the square
#include "LEDPlaneToCube.h"     // Animation 0

// Put up a single LED then extend it into a line
#include "LEDPointToLine.h"     // Animation 1

// Light up random LEDs with random colors. Erase them now and then to avoid filling the cube.
#include "LEDRandomPoints.h"    // Animation 2

// Fill the layers one at a time with colors that form a color gradient
#include "LEDLinearFill.h"      // Animation 3

// Fire an arc from a corner that falls into an exploding ball
#include "LEDFireworkRocket.h"  // Animation 4

// Fill the layers one at a time with random off/on to look like "surf"
#include "LEDTide.h"            // Animation 5

// Move one or more ball-like objects around the edges of the cube
#include "LEDBall.h"            // Animation 6

// Fill the cube with random colors and randomly change individual LED colors
#include "LEDRandomFull.h"      // Animation 7

// Make white-ish random LEDs start dim, get brighter then dimmer
#include "LEDStarrySky.h"       // Animation 8

// Make a fountain-like flow of LEDs coming up in the center and falling at the edges
#include "LEDFountain.h"        // Animation 9

// Make a flow of LED colors start at the top center and flow down the outer edges
#include "LEDWaterfall.h"       // Animation 10

// Make a square paddle rotate and move around
#include "LEDWindmill.h"        // Animation 11

// Make an LED zip around the edges of the cube, maybe with wings and always with a fading tail
#include "LEDDash.h"            // Animation 12

// Fill in spiral-like shapes with varying thicknesses
#include "LEDSpiral.h"          // Animation 13

// Fill in a horizontal spiral-like single layer, drop each LED to a lower layer then erase
#include "LEDStringFall.h"      // Animation 14

// Light up an outer plane with some shape then have it flop to another outer plane
#include "LEDFlopWall.h"        // Animation 15

// A shape bounces pong-like around in the cube
#include "LEDPong.h"            // Animation 16

// 1, 2 or 3 sets of axes move around. Sometimes lines, sometimes planes.
#include "LEDMovingAxes.h"      // Animation 17

// Patchy volumes fill up with random colors
#include "LEDColorRegion.h"     // Animation 18

// Blocks of random colors slide around one at a time
#include "LEDSlidingCube.h"     // Animation 19

// Try to look like the inside of a tokomak
#include "LEDIter.h"            // Animation 20

// Try to look like a liquid sloshing from one side of the cube to another
#include "LEDSlosh.h"           // Animation 21

// Pools of color in each corner squirt into a center pool
#include "LEDPool.h"            // Animation 22

// Rotate things around the vertical center of the cube
#include "LEDRotor.h"           // Animation 23

// Up to 8 pairs of dots "orbit" eachother and move around the cube
#include "LEDBinary.h"          // Animation 24

// Simple shapes appear, brighten then dim & disappera
#include "LEDShape.h"           // Animation 25

// Run FlopWall (#15) and Pong (#16) at the same time
#include "LEDCombo1.h"          // Animation 26

// Run Ball (#6) and Dash (#12) at the same time
#include "LEDCombo2.h"          // Animation 27

// Randomly pick unlit LEDs and set them to random colors until the cube is all lit
#include "LEDRandomFill.h"      // Animation 28

// Try to look like little spherical "pings" going off
#include "LEDSonar.h"           // Animation 29

// Try to look like a beam sweeping around the cube's vertical center
#include "LEDRadar.h"           // Animation 30

// Draw randomly colored lines
#include "LEDLineFill.h"        // Animation 31

// Make square columns rise and fall
#include "LEDBarGraph.h"        // Animation 32

// A few pillars go around the outside rising and falling in height
#include "LEDMerryGoRound.h"    // Animation 33

// A very fast single line with trail zipping through the whole cube
#include "LEDMarathon.h"        // Animation 34

// Run PointToLine (#1) and Pong (#16) at the same time
#include "LEDCombo3.h"          // Animation 35

// Run Dash (#12) and Marathon (#34) at the same time
#include "LEDCombo4.h"          // Animation 36

// Run FireworkRocket (#4) and Sonar (#29) at the same time
#include "LEDCombo5.h"          // Animation 37

// Run MerryGoRound (#33) and Radar (#30) at the same time
#include "LEDCombo6.h"          // Animation 38

// Run Spiral (#13) and Tide (#5) at the same time
#include "LEDCombo7.h"          // Animation 39

// Light up a corner and expand it to a random extent
#include "LEDCorner.h"          // Animation 40

// Loop a line around like a jump rope
#include "LEDJumpRope.h"        // Animation 41

// Put up a hoop and shoot a ball through it
#include "LEDBasketBall.h"      // Animation 42

// Like "LineFill" but loops instead of lines
#include "LEDLoopFill.h"        // Animation 43


// Pin definitions for LEDs on the iSmart cube's microprocessor PCB:
#define OnboardLEDRed     PB8
#define OnboardLEDGreen   PB9

// Pin definitions for the serial link to Arduino IDE:
#define RX            PA10
#define TX            PA9
HardwareSerial Serial1(RX, TX);

// Timer
HardwareTimer Timer1(TIM1);

// Pin definitions for the buttons on the iSmart cube's main PCB:
#define NextButton        PC1
#define CycleButton       PC2
#define StartPauseButton  PC0
// Button variables:
int NextButtonReading;
int CycleButtonReading;
int StartPauseButtonReading;
int NextButtonLastReading = HIGH;
int CycleButtonLastReading = HIGH;
int StartPauseButtonLastReading = HIGH;
int NextButtonState;
int CycleButtonState;
int StartPauseButtonState;
unsigned long NextButtonDebounceWindowStartTime;
unsigned long CycleButtonDebounceWindowStartTime;
unsigned long StartPauseButtonDebounceWindowStartTime;
unsigned long DebounceWindow = 100;

// Instantiate each of the classes
LEDCube Cube;
LEDMove Move;
LEDPlaneToCube PlaneToCube;
LEDPointToLine PointToLine;
LEDRandomPoints RandomPoints;
LEDLinearFill LinearFill;
LEDFireworkRocket FireworkRocket;
LEDTide Tide;
LEDBall Ball;
LEDRandomFull RandomFull;
LEDStarrySky StarrySky;
LEDFountain Fountain;
LEDWaterfall Waterfall;
LEDWindmill Windmill;
LEDDash Dash;
LEDSpiral Spiral;
LEDStringFall StringFall;
LEDFlopWall FlopWall;
LEDPong Pong;
LEDMovingAxes MovingAxes;
LEDColorRegion ColorRegion;
LEDSlidingCube SlidingCube;
LEDIter Iter;
LEDSlosh Slosh;
LEDPool Pool;
LEDRotor Rotor;
LEDBinary Binary;
LEDShape Shape;
LEDCombo1 Combo1;
LEDCombo2 Combo2;
LEDRandomFill RandomFill;
LEDSonar Sonar;
LEDRadar Radar;
LEDLineFill LineFill;
LEDBarGraph BarGraph;
LEDMerryGoRound MerryGoRound;
LEDMarathon Marathon;
LEDCombo3 Combo3;
LEDCombo4 Combo4;
LEDCombo5 Combo5;
LEDCombo6 Combo6;
LEDCombo7 Combo7;
LEDCorner Corner;
LEDJumpRope JumpRope;
LEDBasketBall BasketBall;
LEDLoopFill LoopFill;

// Serial link to the Arduino IDE
const byte SerialPacketMaximumLength = 8;
byte SerialReceivePacket[SerialPacketMaximumLength];
char SerialSendPacket[SerialPacketMaximumLength];
bool SerialDataAvailable = false; // set to true when a packet has been received.

// Standard Arduino setup() (initialization) routine
void setup() {
  // Onboard LEDs:
  pinMode(OnboardLEDRed, OUTPUT);
  pinMode(OnboardLEDGreen, OUTPUT);

  // Buttons:
  pinMode(NextButton, INPUT);
  pinMode(CycleButton, INPUT);
  pinMode(StartPauseButton, INPUT);

  // Open the serial port and listen at 38400 bps:
  Serial1.begin(38400);

  // Start Timer1
  Timer1.setPrescaleFactor(64);     // 64 MHz crystal / 64 prescale => 1 MHz timer clock
  Timer1.setOverflow(1000);          // counting to 1000 should give us a 1 millisecond timer
  Timer1.attachInterrupt(TimerISR);
  Timer1.refresh();
  Timer1.resume();

  // Shift register library configuration
  SPI.setBitOrder(MSBFIRST);//Most Significant Bit First
  SPI.setDataMode(SPI_MODE0);// Mode 0 Rising edge of data, keep clock low
  SPI.setClockDivider(SPI_CLOCK_DIV2);//Run the data in at 16MHz/2 - 8MHz

  // Start the shift register library
  SPI.begin();

  // Seed the random number generator with a sort-of-genuine random input
  randomSeed(analogRead(PA0));

}

/*
Serial input protocol to interpret serial input from the Arduino IDE's Serial Monitor:
Every packet begins with 'S'.
Every packet ends with '\n'.
If the initial S is followed by a number ('0'..'7') then the packet is
  taken as 6 numbers giving X, Y, Z, R, G and B to set an individual LED.
Other valid 2nd characters:
'A' => set the test mode alternate animation number
'B' => (early diagnostic) draw a ball
'C' => clear the entire cube
'D' => display global values
'E' => stop animation and display a rainbow cube
'G' => set global: 'GBT'/'GBF' = global boolean true/false, 'GI##' = global integer value
'P' => pause the animation
'R' => fill an X-parallel row
'S' => set the test mode animation number
'T' => toggle test mode on/off
'V' => set the animation step period
*/

// Standard Arduino loop() just keeps running again and again after the setup() is done.
//  This routine accomplishes two things:
//    1) updates the physical LEDs in the cube to whatever is in the Cube.Image array.
//    2) act on any serial input which may have come in from the Arduino IDE.
//          .... this serial input will only occur during development when the cube
//          .... is attached by USB cable to the Arduino IDE. When the cube is in
//          .... normal operation with only power being supplied to it, there won't
//          .... be any serial activity.
void loop() {
  // 1) Render stored image to physical LEDs:
  Cube.RenderImageToPhysicalCube();  

  // 2) Check for serial input
  ReadIncomingSerial();
  if (SerialDataAvailable == true) {
    // A serial packet has arrived
    SerialDataAvailable = false;
    Serial1.println("OK");
    if ((SerialReceivePacket[1] == 'A') || (SerialReceivePacket[1] == 'a')) {
      // Set the test alternate to the given number
      Cube.SetTestAlternateIndex(GetSerialDecimalArgument());
    } else if ((SerialReceivePacket[1] == 'B') || (SerialReceivePacket[1] == 'b')) {
      // Draw a ball
      Ball.DrawBall(3, 3, 3, 3, 3, 3);
    } else if ((SerialReceivePacket[1] == 'C') || (SerialReceivePacket[1] == 'c')) {
      // Clear the cube
      Cube.ClearImage();
    } else if ((SerialReceivePacket[1] == 'D') || (SerialReceivePacket[1] == 'd')) {
      Serial1.print("Global boolean: ");
      Serial1.print(Cube.GetGlobalBoolean());
      Serial1.print(", integer: ");
      Serial1.println(Cube.GetGlobalInteger());
    } else if ((SerialReceivePacket[1] == 'E') || (SerialReceivePacket[1] == 'e')) {
      Cube.ToggleAnimationPaused();
      Cube.PaintRainbow();
    } else if ((SerialReceivePacket[1] == 'G') || (SerialReceivePacket[1] == 'g')) {
      switch (SerialReceivePacket[2]) {
      case 'B':
      case 'b':
        switch (SerialReceivePacket[3]) {
        case 'T':
        case 't':
          Cube.SetGlobalBoolean(true);
          break;
        case 'F':
        case 'f':
          Cube.SetGlobalBoolean(false);
          break;
        default:
          Serial1.print("!! unrecognized global boolean new value: ");
          Serial1.println(SerialReceivePacket[3]);
          break;
        }
        break;
      case 'I':
      case 'i':
        Cube.SetGlobalInteger(GetSerialDecimalArgument2());
        break;
      default:
        Serial1.print("!! unrecognized sub-function character: ");
        Serial1.println(SerialReceivePacket[2]);
        break;
      }
    } else if ((SerialReceivePacket[1] == 'P') || (SerialReceivePacket[1] == 'p')) {
      Cube.ToggleAnimationPaused();
    } else if ((SerialReceivePacket[1] == 'R') || (SerialReceivePacket[1] == 'r')) {
      // Fill all X positions 
      byte Y = HexCharToByte(SerialReceivePacket[2]);
      byte Z = HexCharToByte(SerialReceivePacket[3]);
      byte R = HexCharToByte(SerialReceivePacket[4]);
      byte G = HexCharToByte(SerialReceivePacket[5]);
      byte B = HexCharToByte(SerialReceivePacket[6]);
      for (int X = 0; X < 8; X++) {
        Cube.SetLEDColor(X, Y, Z, R, G, B);
      }
    // } else if ((SerialReceivePacket[1] == 'S') || (SerialReceivePacket[1] == 's')) {
    //   // Return an analog read
    //   int AnalogInput = analogRead(PA0);
    //   Serial1.println(AnalogInput);
    } else if ((SerialReceivePacket[1] == 'S') || (SerialReceivePacket[1] == 's')) {
      // Set the test animation to the given number
      Cube.SetTestAnimationIndex(GetSerialDecimalArgument());
    } else if ((SerialReceivePacket[1] == 'T') || (SerialReceivePacket[1] == 't')) {
      Cube.ToggleTestMode();
      Serial1.write("Testmode: ");
      Serial1.println(Cube.GetTestMode());
    } else if ((SerialReceivePacket[1] == 'V') || (SerialReceivePacket[1] == 'v')) {
      Cube.SetAnimationStepSpeedPeriodTo(GetSerialDecimalArgument());
    } else {
      // Set a particular LED
      byte X = HexCharToByte(SerialReceivePacket[1]);
      byte Y = HexCharToByte(SerialReceivePacket[2]);
      byte Z = HexCharToByte(SerialReceivePacket[3]);
      byte R = HexCharToByte(SerialReceivePacket[4]);
      byte G = HexCharToByte(SerialReceivePacket[5]);
      byte B = HexCharToByte(SerialReceivePacket[6]);
      Cube.SetLEDColor(X, Y, Z, R, G, B);
    } // end else-if(SerialReceivePacket
  } // end if (SerialDataAvailable

  // 3) Check for button press
  // ... Pick up the current state of the buttons
  NextButtonReading = digitalRead(NextButton);
  CycleButtonReading = digitalRead(CycleButton);
  StartPauseButtonReading = digitalRead(StartPauseButton);
  // ... Reset the debounce window any time a switch state changes
  if (NextButtonReading != NextButtonLastReading) {
    NextButtonDebounceWindowStartTime = millis();
  }
  if (CycleButtonReading != CycleButtonLastReading) {
    CycleButtonDebounceWindowStartTime = millis();
  }
  if (StartPauseButtonReading != StartPauseButtonLastReading) {
    StartPauseButtonDebounceWindowStartTime = millis();
  }
  // ... If the debounce window time has expired then the switch state is valid
  if ((millis() - NextButtonDebounceWindowStartTime) > DebounceWindow) {
    // ... The Next button reading is valid - has it changed from the previous state?
    if (NextButtonReading != NextButtonState) {
      // ... The state of the Next button has changed.
      // .... Save the new state
      NextButtonState = NextButtonReading;
      // .... Did it just get pressed or released?
      if (LOW == NextButtonState) {
        // Pressed
        Serial1.println("Next button pressed");
      } else {
        // Released
        Serial1.println("Next button released");
      }
    }
  }
  // Same procedure for the other two buttons
  if ((millis() - CycleButtonDebounceWindowStartTime) > DebounceWindow) {
    if (CycleButtonReading != CycleButtonState) {
      CycleButtonState = CycleButtonReading;
      if (LOW == CycleButtonState) {
        Serial1.println("Cycle button pressed");
      } else {
        Serial1.println("Cycle button released");
      }
    }
  }
  if ((millis() - StartPauseButtonDebounceWindowStartTime) > DebounceWindow) {
    if (StartPauseButtonReading != StartPauseButtonState) {
      StartPauseButtonState = StartPauseButtonReading;
      if (LOW == StartPauseButtonState) {
        Serial1.println("StartPause button pressed");
      } else {
        Serial1.println("StartPause button released");
      }
    }
  }

  // ... Save the current readings for next time through the loop
  NextButtonLastReading = NextButtonReading;
  CycleButtonLastReading = CycleButtonReading;
  StartPauseButtonLastReading = StartPauseButtonReading;
}

// Interrupt service routine for Timer1 - Register A compare match ("TIMER1_COMPA_vect" is predefined for the hardware vector)
// This routine is called once each millisecond by the hardware timer. It calls the
// "AnimationStepThrottle()" in the Cube class which in turn sorts out which animation
// is currently running and calls that animation's "Step" routine to "animate the animation".
void TimerISR(void) {
  Cube.AnimationStepThrottle();
}

// This routine is repeatedly called by the Arduino loop() routine. It detects any
//  incoming serial traffic and breaks it into packets for the loop() routine to process.
void ReadIncomingSerial() {
  static bool SerialReceiveIsOngoing = false;
  static byte CurrentSerialIndex = 0;
  byte CurrentReceivedByte;

  while (Serial1.available() > 0 && SerialDataAvailable == false) {
    CurrentReceivedByte = Serial1.read();
    if (SerialReceiveIsOngoing == true) {
      // We're in the process of receiving a packet so place theis received byte into the receive buffer
      SerialReceivePacket[CurrentSerialIndex] = CurrentReceivedByte;
      CurrentSerialIndex++;
      if (CurrentReceivedByte == '\n') {
        // This was the final character of the serial packet
        SerialDataAvailable = true;
        SerialReceiveIsOngoing = false;
        for (int i = 0; i < SerialPacketMaximumLength; i++) {
          SerialSendPacket[i] = char(SerialReceivePacket[i]);
        }
        Serial1.write(SerialSendPacket);
      }
    } else {
      // We're waiting for the packet start character
      if ((CurrentReceivedByte == 'S') || (CurrentReceivedByte == 's')) {
        // This is the start of a new packet
        SerialReceiveIsOngoing = true;
        SerialReceivePacket[0] = 'S';
        CurrentSerialIndex = 1;
      }
    }
  }
}


// Utility routine to convert serial ASCII characters to equivalent binary integer values.
byte HexCharToByte(char hex) {
  switch(hex) {
    case '0':
      return 0;
      break;
    case '1':
      return 1;
      break;
    case '2':
      return 2;
      break;
    case '3':
      return 3;
      break;
    case '4':
      return 4;
      break;
    case '5':
      return 5;
      break;
    case '6':
      return 6;
      break;
    case '7':
      return 7;
      break;
    case '8':
      return 8;
      break;
    case '9':
      return 9;
      break;
    case 'A':
    case 'a':
      return 10;
      break;
    case 'B':
    case 'b':
      return 11;
      break;
    case 'C':
    case 'c':
      return 12;
      break;
    case 'D':
    case 'd':
      return 13;
      break;
    case 'E':
    case 'e':
      return 14;
      break;
    case 'F':
    case 'f':
      return 15;
      break;
    default:
      return 0;
      break;
  }
}

// Utility routine that returns an integer value following a single-character serial function code
int GetSerialDecimalArgument() {
  // SerialReceivePacket[0] is always an 'S'
  // SerialReceivePacket[1] is a function code
  // SerialReceivePacket[2..4] can be a decimal argument ranging from 0 to 999
  int ReturnValue = 0;
  if (SerialReceivePacket[3] == '\n') {
    // It's a single digit
    ReturnValue = HexCharToByte(SerialReceivePacket[2]);
  } else if (SerialReceivePacket[4] == '\n') {
    // It's a two digit value
    ReturnValue = HexCharToByte(SerialReceivePacket[2]) * 10 + HexCharToByte(SerialReceivePacket[3]);
  } else if (SerialReceivePacket[5] == '\n') {
    // It's a three digit value
    ReturnValue = HexCharToByte(SerialReceivePacket[2]) * 100 + HexCharToByte(SerialReceivePacket[3]) * 10 + HexCharToByte(SerialReceivePacket[4]);
  } else {
    // ???
    ReturnValue = 0;
  }
  return ReturnValue;
}

// Utility routine that returns an integer value following a double-character serial function code
int GetSerialDecimalArgument2() {
  // ...same as above but decimal argument begins in position 3 rather than 2 (e.g. 'SGI###')
  int ReturnValue = 0;
  if (SerialReceivePacket[4] == '\n') {
    // It's a single digit
    ReturnValue = HexCharToByte(SerialReceivePacket[3]);
  } else if (SerialReceivePacket[5] == '\n') {
    // It's a two digit value
    ReturnValue = HexCharToByte(SerialReceivePacket[3]) * 10 + HexCharToByte(SerialReceivePacket[4]);
  } else if (SerialReceivePacket[6] == '\n') {
    // It's a three digit value
    ReturnValue = HexCharToByte(SerialReceivePacket[3]) * 100 + HexCharToByte(SerialReceivePacket[4]) * 10 + HexCharToByte(SerialReceivePacket[5]);
  } else {
    // ???
    ReturnValue = 0;
  }
  return ReturnValue;
}
