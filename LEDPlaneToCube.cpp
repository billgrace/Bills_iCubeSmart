// LEDPlaneToCube.cpp

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

LEDPlaneToCube::LEDPlaneToCube() {
  XIncrement = 1;
  YIncrement = 1;
  ZIncrement = 1;
}

int LEDPlaneToCube::SuggestedNumberOfAnimationCycles() {
	return random(7, 15);
}

void LEDPlaneToCube::StartPlaneToCube() {
	// Register the start of a new animation cycle
	Cube.IncrementAnimationDurationCycleCount();
	Cube.ClearImage();

	// Pick a random color
  Red = random(0, 8);
  Green = random(0, 8);
  Blue = random(0, 8);

	// Pick a random size
  CubeEdgeSize = random( 3, 9);

	// Pick a sort-of-random animation speed
  	// Slower for small, faster for large:
  	// Cube size 	Period
  	//		3		100
  	//		4		 90
  	//		5		 80
  	//		6		 70
  	//		7		 60
  	//		8		 50
  switch(CubeEdgeSize) {
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

  int MaxMinX = 8 - CubeEdgeSize;
  MinX = random(0, MaxMinX + 1);
  MaxX = MinX + CubeEdgeSize - 1;
  MinY = random(0, MaxMinX + 1);
  MaxY = MinY + CubeEdgeSize - 1;
  MinZ = random(0, MaxMinX + 1);
  MaxZ = MinZ + CubeEdgeSize - 1;
  CurrentNormalAxis = random(0, 6);
  switch(CurrentNormalAxis) {
    case 0:
      CurrentX = MinX;
      XIncrement = 1;
      break;
    case 1:
      CurrentX = MaxX;
      XIncrement = -1;
      break;
    case 2:
      CurrentY = MinY;
      YIncrement = 1;
      break;
    case 3:
      CurrentY = MaxY;
      YIncrement = -1;
      break;
    case 4:
      CurrentZ = MinZ;
      ZIncrement = 1;
      break;
    case 5:
      CurrentZ = MaxZ;
      ZIncrement = -1;
      break;
  }
}

void LEDPlaneToCube::StepPlaneToCube() {
	switch(CurrentNormalAxis) {
	case 0:
		if (XIncrement == 1) {
			// Still expanding in +ve X direction
			if (CurrentX >= MaxX) {
				// We've finished the last layer so initiate contraction
				XIncrement = -1;
				// Turn off the last layer as the first contraction move
				for (int y = MinY; y < MaxY; y++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( MaxX, y, z, 0, 0, 0 );
					}
				}
				CurrentX = MaxX-1;
			} else {
				// Turn on the next layer in the expansion
				for (int y = MinY; y < MaxY; y++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( CurrentX, y, z, Red, Green, Blue );
					}
				}
				CurrentX++;
			}
		} else {
			// Contracting
			if (CurrentX < MinX) {
				// We've finished the last layer of contraction so we're done
				Cube.ClearImage();
				StartPlaneToCube();
			} else {
				// Turn off the next layer in the contraction
				for (int y = MinY; y < MaxY; y++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( CurrentX, y, z, 0, 0, 0 );
					}
				}
				CurrentX--;
			}
		}
		break;
	case 1:
		if (XIncrement == -1) {
			// Expanding in -ve X direction
			if (CurrentX <= MinX) {
				XIncrement = 1;
				for (int y = MinY; y < MaxY; y++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor(MinX, y, z, 0, 0, 0);
					}
				}
				CurrentX = MinX+1;
			} else {
				for (int y = MinY; y < MaxY; y++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( CurrentX, y, z, Red, Green, Blue);
					}
				}
				CurrentX--;
			}
		} else {
			if (CurrentX >=MaxX) {
				Cube.ClearImage();
				StartPlaneToCube();
			} else {
				for (int y = MinY; y < MaxY; y++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( CurrentX, y, z, 0, 0, 0 );
					}
				}
				CurrentX++;
			}
		}
		break;
	case 2:
		if (YIncrement == 1) {
			// Still expanding in +ve Y direction
			if (CurrentY >= MaxY) {
				// We've finished the last layer so initiate contraction
				YIncrement = -1;
				// Turn off the last layer as the first contraction move
				for (int x = MinX; x < MaxX; x++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( x, MaxY, z, 0, 0, 0 );
					}
				}
				CurrentY = MaxY-1;
			} else {
				// Turn on the next layer in the expansion
				for (int x = MinX; x < MaxX; x++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( x, CurrentY, z, Red, Green, Blue );
					}
				}
				CurrentY++;
			}
		} else {
			// Contracting
			if (CurrentY < MinY) {
				// We've finished the last layer of contraction so we're done
				Cube.ClearImage();
				StartPlaneToCube();
			} else {
				// Turn off the next layer in the contraction
				for (int x = MinX; x < MaxX; x++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( x, CurrentY, z, 0, 0, 0 );
					}
				}
				CurrentY--;
			}
		}
		break;
	case 3:
		if (YIncrement == -1) {
			// Expanding in -ve Y direction
			if (CurrentY <= MinY) {
				YIncrement = 1;
				for (int x = MinX; x < MaxX; x++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor(x, MinY, z, 0, 0, 0);
					}
				}
				CurrentY = MinY + 1;
			} else {
				for (int x = MinX; x < MaxX; x++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( x, CurrentY, z, Red, Green, Blue);
					}
				}
				CurrentY--;
			}
		} else {
			if (CurrentY >=MaxY) {
				Cube.ClearImage();
				StartPlaneToCube();
			} else {
				for (int x = MinX; x < MaxX; x++) {
					for (int z = MinZ; z < MaxZ; z++) {
						Cube.SetLEDColor( x, CurrentY, z, 0, 0, 0 );
					}
				}
				CurrentY++;
			}
		}
		break;
	case 4:
		if (ZIncrement == 1) {
			// Still expanding in +ve Z direction
			if (CurrentZ >= MaxZ) {
				// We've finished the last layer so initiate contraction
				ZIncrement = -1;
				// Turn off the last layer as the first contraction move
				for (int x = MinX; x < MaxX; x++) {
					for (int y = MinY; y < MaxY; y++) {
						Cube.SetLEDColor( x, y, MaxZ, 0, 0, 0 );
					}
				}
				CurrentZ = MaxZ-1;
			} else {
				// Turn on the next layer in the expansion
				for (int x = MinX; x < MaxX; x++) {
					for (int y = MinY; y < MaxY; y++) {
						Cube.SetLEDColor( x, y, CurrentZ, Red, Green, Blue );
					}
				}
				CurrentZ++;
			}
		} else {
			// Contracting
			if (CurrentZ < MinZ) {
				// We've finished the last layer of contraction so we're done
				Cube.ClearImage();
				StartPlaneToCube();
			} else {
				// Turn off the next layer in the contraction
				for (int x = MinX; x < MaxX; x++) {
					for (int y = MinY; y < MaxY; y++) {
						Cube.SetLEDColor( x, y, CurrentZ, 0, 0, 0 );
					}
				}
				CurrentZ--;
			}
		}
		break;
	case 5:
		if (ZIncrement == -1) {
			// Expanding in -ve Z direction
			if (CurrentZ <= MinZ) {
				ZIncrement = 1;
				for (int x = MinX; x < MaxX; x++) {
					for (int y = MinY; y < MaxY; y++) {
						Cube.SetLEDColor(x, y, MinZ, 0, 0, 0);
					}
				}
				CurrentZ = MinZ+1;
			} else {
				for (int x = MinX; x < MaxX; x++) {
					for (int y = MinY; y < MaxY; y++) {
						Cube.SetLEDColor( x, y, CurrentZ, Red, Green, Blue);
					}
				}
				CurrentZ--;
			}
		} else {
			if (CurrentZ >=MaxZ) {
				Cube.ClearImage();
				StartPlaneToCube();
			} else {
				for (int x = MinX; x < MaxX; x++) {
					for (int y = MinY; y < MaxY; y++) {
						Cube.SetLEDColor( x, y, CurrentZ, 0, 0, 0 );
					}
				}
				CurrentZ++;
			}
		}
		break;
	}
}

