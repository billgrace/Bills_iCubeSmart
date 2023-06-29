// LEDWindmill.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDWindmill.h"

extern LEDCube Cube;
extern LEDWindmill Windmill;

LEDWindmill::LEDWindmill() {

}

int LEDWindmill::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDWindmill::StartWindmill() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(50, 80));
	MaxNumberOfSteps = random(200, 500);
	Mode = random(0, 2);
	StepCount = 0;
	switch(random(0, 24)) {
	case 0:
		CenterX = 2;
		CenterY = 2;
		CenterZ = 2;
		CenterDirection = 0;
		break;
	case 1:
		CenterX = 2;
		CenterY = 2;
		CenterZ = 2;
		CenterDirection = 1;
		break;
	case 2:
		CenterX = 2;
		CenterY = 2;
		CenterZ = 2;
		CenterDirection = 2;
		break;
	case 3:
		CenterX = 5;
		CenterY = 2;
		CenterZ = 2;
		CenterDirection = 3;
		break;
	case 4:
		CenterX = 5;
		CenterY = 2;
		CenterZ = 2;
		CenterDirection = 1;
		break;
	case 5:
		CenterX = 5;
		CenterY = 2;
		CenterZ = 2;
		CenterDirection = 2;
		break;
	case 6:
		CenterX = 2;
		CenterY = 5;
		CenterZ = 2;
		CenterDirection = 0;
		break;
	case 7:
		CenterX = 2;
		CenterY = 5;
		CenterZ = 2;
		CenterDirection = 4;
		break;
	case 8:
		CenterX = 2;
		CenterY = 5;
		CenterZ = 2;
		CenterDirection = 2;
		break;
	case 9:
		CenterX = 5;
		CenterY = 5;
		CenterZ = 2;
		CenterDirection = 3;
		break;
	case 10:
		CenterX = 5;
		CenterY = 5;
		CenterZ = 2;
		CenterDirection = 4;
		break;
	case 11:
		CenterX = 5;
		CenterY = 5;
		CenterZ = 2;
		CenterDirection = 2;
		break;
	case 12:
		CenterX = 2;
		CenterY = 2;
		CenterZ = 5;
		CenterDirection = 0;
		break;
	case 13:
		CenterX = 2;
		CenterY = 2;
		CenterZ = 5;
		CenterDirection = 1;
		break;
	case 14:
		CenterX = 2;
		CenterY = 2;
		CenterZ = 5;
		CenterDirection = 5;
		break;
	case 15:
		CenterX = 5;
		CenterY = 2;
		CenterZ = 5;
		CenterDirection = 3;
		break;
	case 16:
		CenterX = 5;
		CenterY = 2;
		CenterZ = 5;
		CenterDirection = 1;
		break;
	case 17:
		CenterX = 5;
		CenterY = 2;
		CenterZ = 5;
		CenterDirection = 5;
		break;
	case 18:
		CenterX = 2;
		CenterY = 5;
		CenterZ = 5;
		CenterDirection = 0;
		break;
	case 19:
		CenterX = 2;
		CenterY = 5;
		CenterZ = 5;
		CenterDirection = 4;
		break;
	case 20:
		CenterX = 2;
		CenterY = 5;
		CenterZ = 5;
		CenterDirection = 5;
		break;
	case 21:
		CenterX = 5;
		CenterY = 5;
		CenterZ = 5;
		CenterDirection = 3;
		break;
	case 22:
		CenterX = 5;
		CenterY = 5;
		CenterZ = 5;
		CenterDirection = 4;
		break;
	case 23:
		CenterX = 5;
		CenterY = 5;
		CenterZ = 5;
		CenterDirection = 5;
		break;
	}
	Angle = 0;
	CenterDirection = 0;
	Red = Cube.RandomColor();
	Green = Cube.RandomColor();
	Blue = Cube.RandomColor();
	CounterRed = Cube.RandomColor();
	CounterGreen = Cube.RandomColor();
	CounterBlue = Cube.RandomColor();
	RotationsAtEachCenter = random(2, 4);
	RotationCount = 0;
	CenterMovesPerColorChange = random(2, 4);
	CenterMoveCount = 0;
}

void LEDWindmill::StepWindmill() {
	StepCount++;
	if (StepCount >= MaxNumberOfSteps) {
		StartWindmill();
	}
	DrawBlade(false);
	Angle++;
	if (Angle >= 8) {
		Angle = 0;
		RotationCount++;
		if (RotationCount >= RotationsAtEachCenter) {
			MoveToNextCenter();
		}
	}
	DrawBlade(true);
}

void LEDWindmill::DrawBlade(bool OnOrOff) {
	int R;
	int G;
	int B;
	int CR;
	int CG;
	int CB;
	if (OnOrOff) {
		R = Red;
		G = Green;
		B = Blue;
		CR = CounterRed;
		CG = CounterGreen;
		CB = CounterBlue;
	} else {
		R = 0;
		G = 0;
		B = 0;
		CR = 0;
		CG = 0;
		CB = 0;
	}
	switch(Angle) {
	case 0:
		DeltaX = 1;
		DeltaY = 0;
		CounterDeltaX = 1;
		CounterDeltaY = 1;
		break;
	case 1:
		DeltaX = 1;
		DeltaY = -1;
		CounterDeltaX = 0;
		CounterDeltaY = 1;
		break;
	case 2:
		DeltaX = 0;
		DeltaY = -1;
		CounterDeltaX = -1;
		CounterDeltaY = 1;
		break;
	case 3:
		DeltaX = -1;
		DeltaY = -1;
		CounterDeltaX = -1;
		CounterDeltaY = 0;
		break;
	case 4:
		DeltaX = -1;
		DeltaY = 0;
		CounterDeltaX = -1;
		CounterDeltaY = -1;
		break;
	case 5:
		DeltaX = -1;
		DeltaY = 1;
		CounterDeltaX = 0;
		CounterDeltaY = -1;
		break;
	case 6:
		DeltaX = 0;
		DeltaY = 1;
		CounterDeltaX = 1;
		CounterDeltaY = -1;
		break;
	case 7:
		DeltaX = 1;
		DeltaY = 1;
		CounterDeltaX = 1;
		CounterDeltaY = 0;
		break;
	}
	for (int Level = CenterZ - 2; Level < CenterZ + 3; Level++) {
		if ((Mode == 0) && (((Level == (CenterZ - 1)) || (Level == (CenterZ + 1))))) {
			Cube.SetLEDColor(CenterX - 2 * CounterDeltaX, CenterY + 2 * CounterDeltaY, Level, CR, CG, CB);
			Cube.SetLEDColor(CenterX - CounterDeltaX, CenterY + CounterDeltaY, Level, CR, CG, CB);
			Cube.SetLEDColor(CenterX, CenterY, Level, CR, CG, CB);
			Cube.SetLEDColor(CenterX + CounterDeltaX, CenterY - CounterDeltaY, Level, CR, CG, CB);
			Cube.SetLEDColor(CenterX + 2 * CounterDeltaX, CenterY - 2 * CounterDeltaY, Level, CR, CG, CB);
		} else {
			Cube.SetLEDColor(CenterX - 2 * DeltaX, CenterY + 2 * DeltaY, Level, R, G, B);
			Cube.SetLEDColor(CenterX - DeltaX, CenterY + DeltaY, Level, R, G, B);
			Cube.SetLEDColor(CenterX, CenterY, Level, R, G, B);
			Cube.SetLEDColor(CenterX + DeltaX, CenterY - DeltaY, Level, R, G, B);
			Cube.SetLEDColor(CenterX + 2 * DeltaX, CenterY - 2 * DeltaY, Level, R, G, B);
		}
	}
}

void LEDWindmill::MoveToNextCenter() {
	switch (CenterDirection) {
	case 0:
		// Currently moving in +X direction
		if (CenterX < 5) {
			CenterX++;
		} else {
			// Need to change direction
			LEDWindmill::TurnACorner();
		}
		break;
	case 1:
		// Currently moving in +Y direction
		if (CenterY < 5) {
			CenterY++;
		} else {
			// Need to change direction
			LEDWindmill::TurnACorner();
		}
		break;
	case 2:
		// Currently moving in +Z direction
		if (CenterZ < 5) {
			CenterZ++;
		} else {
			// Need to change direction
			LEDWindmill::TurnACorner();
		}
		break;
	case 3:
		// Currently moving in -X direction
		if (CenterX > 2) {
			CenterX--;
		} else {
			// Need to change direction
			LEDWindmill::TurnACorner();
		}
		break;
	case 4:
		// Currently moving in -Y direction
		if (CenterY > 2) {
			CenterY--;
		} else {
			// Need to change direction
			LEDWindmill::TurnACorner();
		}
		break;
	case 5:
		// Currently moving in -Z direction
		if (CenterZ > 2) {
			CenterZ--;
		} else {
			// Need to change direction
			LEDWindmill::TurnACorner();
		}
		break;
	}
	CenterMoveCount++;
	if (CenterMoveCount >= CenterMovesPerColorChange) {
		NewColor = Cube.VeryCloseColor(Red, Green, Blue);
		Red = Cube.RedPartOf(NewColor);
		Green = Cube.GreenPartOf(NewColor);
		Blue = Cube.BluePartOf(NewColor);
		NewColor = Cube.VeryCloseColor(CounterRed, CounterGreen, CounterBlue);
		CounterRed = Cube.RedPartOf(NewColor);
		CounterGreen = Cube.GreenPartOf(NewColor);
		CounterBlue = Cube.BluePartOf(NewColor);
	}
}

void LEDWindmill::TurnACorner() {
	switch(CenterDirection) {
	case 0:
		// Change from +X to Y or Z
		switch(random(0, 2)) {
		case 0:
			if (CenterY < 4) {
				CenterDirection = 1;
				CenterY++;
			} else {
				CenterDirection = 4;
				CenterY--;
			}
			break;
		case 1:
			if (CenterZ < 4) {
				CenterDirection = 2;
				CenterZ++;
			} else {
				CenterDirection = 5;
				CenterZ--;
			}
			break;
		}
		break;
	case 1:
		// Change from +Y to X or Z
		switch(random(0, 2)) {
		case 0:
			if (CenterX < 4) {
				CenterDirection = 0;
				CenterX++;
			} else {
				CenterDirection = 3;
				CenterX--;
			}
			break;
		case 1:
			if (CenterZ < 4) {
				CenterDirection = 2;
				CenterZ++;
			} else {
				CenterDirection = 5;
				CenterZ--;
			}
			break;
		}
		break;
	case 2:
		// Change from +Z to X or Y
		switch(random(0, 2)) {
		case 0:
			if (CenterX < 4) {
				CenterDirection = 0;
				CenterX++;
			} else {
				CenterDirection = 3;
				CenterX--;
			}
			break;
		case 1:
			if (CenterY < 4) {
				CenterDirection = 1;
				CenterY++;
			} else {
				CenterDirection = 4;
				CenterY--;
			}
			break;
		}
		break;
	case 3:
		// Change from -X to Y or Z
		switch(random(0, 2)) {
		case 0:
			if (CenterY < 4) {
				CenterDirection = 1;
				CenterY++;
			} else {
				CenterDirection = 4;
				CenterY--;
			}
			break;
		case 1:
			if (CenterZ < 4) {
				CenterDirection = 2;
				CenterZ++;
			} else {
				CenterDirection = 5;
				CenterZ--;
			}
			break;
		}
		break;
	case 4:
		// Change from -Y to X or Z
		switch(random(0, 2)) {
		case 0:
			if (CenterX < 4) {
				CenterDirection = 0;
				CenterX++;
			} else {
				CenterDirection = 3;
				CenterX--;
			}
			break;
		case 1:
			if (CenterZ < 4) {
				CenterDirection = 2;
				CenterZ++;
			} else {
				CenterDirection = 5;
				CenterZ--;
			}
			break;
		}
		break;
	case 5:
		// Change from -Z to X or Y
		switch(random(0, 2)) {
		case 0:
			if (CenterX < 4) {
				CenterDirection = 0;
				CenterX++;
			} else {
				CenterDirection = 3;
				CenterX--;
			}
			break;
		case 1:
			if (CenterY < 4) {
				CenterDirection = 1;
				CenterY++;
			} else {
				CenterDirection = 4;
				CenterY--;
			}
			break;
		}
		break;
	}
}
