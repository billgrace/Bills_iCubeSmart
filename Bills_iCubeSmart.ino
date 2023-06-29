// Bill_s_iCubeSmart

#include <Arduino.h>
#include <SPI.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDPlaneToCube.h"     // Animation 0
#include "LEDPointToLine.h"     // Animation 1
#include "LEDRandomPoints.h"    // Animation 2
#include "LEDLinearFill.h"      // Animation 3
#include "LEDFireworkRocket.h"  // Animation 4
#include "LEDTide.h"            // Animation 5
#include "LEDBall.h"            // Animation 6
#include "LEDRandomFull.h"      // Animation 7
#include "LEDStarrySky.h"       // Animation 8
#include "LEDFountain.h"        // Animation 9
#include "LEDWaterfall.h"       // Animation 10
#include "LEDWindmill.h"        // Animation 11
#include "LEDDash.h"            // Animation 12
#include "LEDSpiral.h"          // Animation 13
#include "LEDStringFall.h"      // Animation 14
#include "LEDFlopWall.h"        // Animation 15
#include "LEDPong.h"            // Animation 16
#include "LEDMovingAxes.h"      // Animation 17
#include "LEDColorRegion.h"     // Animation 18
#include "LEDSlidingCube.h"     // Animation 19
#include "LEDIter.h"            // Animation 20
#include "LEDSlosh.h"           // Animation 21
#include "LEDPool.h"            // Animation 22
#include "LEDRotor.h"           // Animation 23
#include "LEDBinary.h"          // Animation 24


// Onboard LEDs:
#define OnboardLEDRed     PB8
#define OnboardLEDGreen   PB9

// Serial link to IDE:
#define RX            PA10
#define TX            PA9
HardwareSerial Serial1(RX, TX);

// Timer
HardwareTimer Timer1(TIM1);

// Onboard buttons:
#define StartButton   PC0
#define NextButton    PC1
#define CycleButton   PC2
// Current button states:
bool StartButtonPressed = false;
bool NextButtonPressed = false;
bool CycleButtonPressed = false;
// Button debounce counters:
int StartButtonDebounceCounter = 0;
int NextButtonDebounceCounter = 0;
int CycleButtonDebounceCounter = 0;

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

// Serial input (development diagnostic) protocol:
// Each serial packet starts with 'S' and ends with '\n'.
// The data between the S and \n is one of:
//   nnnnnn => XYZ coordinates (0..7) followed by RGB intensities (0..F)
//   C => clear the entire cube
const byte SerialPacketMaximumLength = 8;
byte SerialReceivePacket[SerialPacketMaximumLength];
char SerialSendPacket[SerialPacketMaximumLength];
bool SerialDataAvailable = false; // set to true when a packet has been received.

void setup() {
  // Onboard LEDs:
  pinMode(OnboardLEDRed, OUTPUT);
  pinMode(OnboardLEDGreen, OUTPUT);

  // Buttons:
  pinMode(StartButton, INPUT);
  pinMode(NextButton, INPUT);
  pinMode(CycleButton, INPUT);

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

// Interrupt service routine for Timer1 Register A compare match ("TIMER1_COMPA_vect" is predefined for the hardware vector)
void TimerISR(void) {
  Cube.AnimationStepThrottle();
}

void ReadIncomingSerial() {
  static boolean SerialReceiveIsOngoing = false;
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

/*
Serial input protocol
Every packet begins with 'S'.
Every packet ends with '\n'.
If the initial S is followed by a number ('0'..'7') then the packet is
  taken as 6 numbers giving X, Y, Z, R, G and B to set an individual LED.
Other valid 2nd characters:
'A' => set the test mode alternate animation number
'B' => (early diagnostic) draw a ball
'C' => clear the entire cube
'D' => display global values
'G' => set global: 'GBT'/'GBF' = global boolean true/false, 'GI##' = global integer value
'P' => pause the animation
'S' => set the test mode animation number
'T' => toggle test mode on/off
'V' => set the animation step period
*/

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
}
