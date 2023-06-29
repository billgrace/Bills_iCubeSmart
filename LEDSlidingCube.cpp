// LEDSlidingCube.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDSlidingCube.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDSlidingCube SlidingCube;

LEDSlidingCube::LEDSlidingCube() {
}

int LEDSlidingCube::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDSlidingCube::StartSlidingCube() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(150);
	NumberOfCubes = Cube.RandomPickOfTwo(8, 64);
	StepCounter = 0;
	StepCountTarget = random(300, 400);
	switch(random(0, 3)){
	case 0:
		// Fill in all the cubes but leave one empty
		Mode = 0;
		Stage = 1;
		break;
	case 1:
		// Start with sliding the empty around to fill in the cubes
		Mode = 0;
		Stage = 2;
		break;
	case 2:
		// Fill in all the cubes and vary the colors without sliding an empty
		Mode = 1;
		Stage = 1;
		break;
	}
	SlideDirection = 0;
	for (int i = 0; i < NumberOfCubes; i++) {
		Colors[i][0] = Cube.RandomColor();
		Colors[i][1] = Cube.RandomColor();
		Colors[i][2] = Cube.RandomColor();
	}
	EmptyIndex = random(0, NumberOfCubes);
	SourceIndex = 0;
	switch(NumberOfCubes) {
	case 8:
		EdgeLength = 4;
		break;
	case 64:
		EdgeLength = 2;
		break;
	}
}

void LEDSlidingCube::StepSlidingCube() {
	StepCounter++;
	if (StepCounter >= StepCountTarget) {
		StartSlidingCube();
	} else {
		switch(Stage) {
		case 1:
			// Initialize the cubes
			if ((SourceIndex != EmptyIndex) || (Mode == 1)) {
				DrawACube(SourceIndex);
				}
			SourceIndex++;
			if (SourceIndex >= NumberOfCubes) {
				// Move on to Stage 2
				Stage = 2;
				PickASourceIndex();
			}
			break;
		case 2:
			if (SlideOffset >= EdgeLength) {
				EmptyIndex = NewEmptyIndex;
				PickASourceIndex();
			} else {
				SlideTheCubeOneStep();
			}
			break;
		}
	}
}

void LEDSlidingCube::DrawACube(int Index) {
	int Red;
	int Green;
	int Blue;
	int CornerCompositeCoordinate;
	int CornerX;
	int CornerY;
	int CornerZ;
	Red = Colors[Index][0];
	Green = Colors[Index][1];
	Blue = Colors[Index][2];
	CornerCompositeCoordinate = GetCornerCompositeCoordinate(Index);
	CornerX = Cube.XPartOf(CornerCompositeCoordinate);
	CornerY = Cube.YPartOf(CornerCompositeCoordinate);
	CornerZ = Cube.ZPartOf(CornerCompositeCoordinate);
	for (int X = 0; X < EdgeLength; X++) {
		for (int Y = 0; Y < EdgeLength; Y++) {
			for (int Z = 0; Z < EdgeLength; Z++) {
				Cube.SetLEDColor(X + CornerX, Y + CornerY, Z + CornerZ, Red, Green, Blue);
			}
		}
	}
}

void LEDSlidingCube::PickASourceIndex() {
	int ProposedSlideDirection;
	XOffset = 1;
	SlideOffset = 0;
	// Figure Y and Z index offsets
	switch(NumberOfCubes) {
	case 8:
		YOffset = 2;
		ZOffset = 4;
		break;
	case 64:
		YOffset = 4;
		ZOffset = 16;
		break;
	}
	// Pick a random direction from the current empty.
	// 0..5 => +X, -X, +Y, -Y, +Z, -Z
	// Avoid going back against the previous direction
	switch(SlideDirection) {
	case 0:
	case 1:
		ProposedSlideDirection = Cube.RandomPickOfFour(2, 3, 4, 5);
		break;
	case 2:
	case 3:
		ProposedSlideDirection = Cube.RandomPickOfFour(0, 1, 4, 5);
		break;
	case 4:
	case 5:
		ProposedSlideDirection = Cube.RandomPickOfFour(0, 1, 2, 3);
		break;
	}
	switch(ProposedSlideDirection) {
	case 0:
		// Try +X
		if (ThereIsACubePlusX()) {
			SourceIndex = EmptyIndex + XOffset;
			SlideDirection = 1;
		} else {
			SourceIndex = EmptyIndex - XOffset;
			SlideDirection = 0;
		}
		break;
	case 1:
		// Try -X
		if (ThereIsACubeMinusX()) {
			SourceIndex = EmptyIndex - XOffset;
			SlideDirection = 0;
		} else {
			SourceIndex = EmptyIndex + XOffset;
			SlideDirection = 1;
		}
		break;
	case 2:
		// Try +Y
		if (ThereIsACubePlusY()) {
			SourceIndex = EmptyIndex + YOffset;
			SlideDirection = 3;
		} else {
			SourceIndex = EmptyIndex - YOffset;
			SlideDirection = 2;
		}
		break;
	case 3:
		// Try -Y
		if (ThereIsACubeMinusY()) {
			SourceIndex = EmptyIndex - YOffset;
			SlideDirection = 2;
		} else {
			SourceIndex = EmptyIndex + YOffset;
			SlideDirection = 3;
		}
		break;
	case 4:
		// Try +Z
		if (ThereIsACubePlusZ()) {
			SourceIndex = EmptyIndex + ZOffset;
			SlideDirection = 5;
		} else {
			SourceIndex = EmptyIndex - ZOffset;
			SlideDirection = 4;
		}
		break;
	case 5:
		// Try -Z
		if (ThereIsACubeMinusZ()) {
			SourceIndex = EmptyIndex - ZOffset;
			SlideDirection = 4;
		} else {
			SourceIndex = EmptyIndex + ZOffset;
			SlideDirection = 5;
		}
		break;
	}
	Colors[EmptyIndex][0] = Colors[SourceIndex][0];
	Colors[EmptyIndex][1] = Colors[SourceIndex][1];
	Colors[EmptyIndex][2] = Colors[SourceIndex][2];
	NewEmptyIndex = SourceIndex;
}

void LEDSlidingCube::SlideTheCubeOneStep() {
	int CornerCompositeCoordinate;
	int SourceCornerX;
	int SourceCornerY;
	int SourceCornerZ;
	int EmptyCornerX;
	int EmptyCornerY;
	int EmptyCornerZ;
	CornerCompositeCoordinate = GetCornerCompositeCoordinate(SourceIndex);
	SourceCornerX = Cube.XPartOf(CornerCompositeCoordinate);
	SourceCornerY = Cube.YPartOf(CornerCompositeCoordinate);
	SourceCornerZ = Cube.ZPartOf(CornerCompositeCoordinate);
	CornerCompositeCoordinate = GetCornerCompositeCoordinate(EmptyIndex);
	EmptyCornerX = Cube.XPartOf(CornerCompositeCoordinate);
	EmptyCornerY = Cube.YPartOf(CornerCompositeCoordinate);
	EmptyCornerZ = Cube.ZPartOf(CornerCompositeCoordinate);
	switch(SlideDirection) {
	case 0:
		// +X
		DrawOneSlice(0, EmptyCornerX + SlideOffset, EmptyCornerY, EmptyCornerZ, Colors[SourceIndex][0], Colors[SourceIndex][1], Colors[SourceIndex][2]);
		if (Mode == 0) {
			DrawOneSlice(0, SourceCornerX + SlideOffset, SourceCornerY, SourceCornerZ, 0, 0, 0);
		}
		break;
	case 1:
		// -X
		DrawOneSlice(0, EmptyCornerX + EdgeLength - 1 - SlideOffset, EmptyCornerY, EmptyCornerZ, Colors[SourceIndex][0], Colors[SourceIndex][1], Colors[SourceIndex][2]);
		if (Mode == 0) {
			DrawOneSlice(0, SourceCornerX + EdgeLength - 1 - SlideOffset, SourceCornerY, SourceCornerZ, 0, 0, 0);
		}
		break;
	case 2:
		// +Y
		DrawOneSlice(1, EmptyCornerX, EmptyCornerY + SlideOffset, EmptyCornerZ, Colors[SourceIndex][0], Colors[SourceIndex][1], Colors[SourceIndex][2]);
		if (Mode == 0) {
			DrawOneSlice(1, SourceCornerX, SourceCornerY + SlideOffset, SourceCornerZ, 0, 0, 0);
		}
		break;
	case 3:
		// -Y
		DrawOneSlice(1, EmptyCornerX, EmptyCornerY + EdgeLength - 1 - SlideOffset, EmptyCornerZ, Colors[SourceIndex][0], Colors[SourceIndex][1], Colors[SourceIndex][2]);
		if (Mode == 0) {
			DrawOneSlice(1, SourceCornerX, SourceCornerY + EdgeLength - 1 - SlideOffset, SourceCornerZ, 0, 0, 0);
		}
		break;
	case 4:
		// +Z
		DrawOneSlice(2, EmptyCornerX, EmptyCornerY, EmptyCornerZ + SlideOffset, Colors[SourceIndex][0], Colors[SourceIndex][1], Colors[SourceIndex][2]);
		if (Mode == 0) {
			DrawOneSlice(2, SourceCornerX, SourceCornerY, SourceCornerZ + SlideOffset, 0, 0, 0);
		}
		break;
	case 5:
		// -Z
		DrawOneSlice(2, EmptyCornerX, EmptyCornerY, EmptyCornerZ + EdgeLength - 1 - SlideOffset, Colors[SourceIndex][0], Colors[SourceIndex][1], Colors[SourceIndex][2]);
		if (Mode == 0) {
			DrawOneSlice(2, SourceCornerX, SourceCornerY, SourceCornerZ + EdgeLength - 1 - SlideOffset, 0, 0, 0);
		}
		break;
	}
	SlideOffset++;
}

void LEDSlidingCube::DrawOneSlice(int NormalAxis, int CornerX, int CornerY, int CornerZ, int Red, int Green, int Blue) {
	switch(NormalAxis) {
	case 0:
		// X is normal axis
		for (int Y = CornerY; Y < CornerY + EdgeLength; Y++) {
			for (int Z = CornerZ; Z < CornerZ + EdgeLength; Z++) {
				Cube.SetLEDColor(CornerX, Y, Z, Red, Green, Blue);
			}
		}
		break;
	case 1:
		// Y is normal axis
		for (int X = CornerX; X < CornerX + EdgeLength; X++) {
			for (int Z = CornerZ; Z < CornerZ + EdgeLength; Z++) {
				Cube.SetLEDColor(X, CornerY, Z, Red, Green, Blue);
			}
		}
		break;
	case 2:
		// Z is normal axis
		for (int X = CornerX; X < CornerX + EdgeLength; X++) {
			for (int Y = CornerY; Y < CornerY + EdgeLength; Y++) {
				Cube.SetLEDColor(X, Y, CornerZ, Red, Green, Blue);
			}
		}
		break;
	}
}

int LEDSlidingCube::GetCornerCompositeCoordinate(int Index) {
	int CornerX;
	int CornerY;
	int CornerZ;
	switch(NumberOfCubes) {
	case 8:
		CornerX = (Index % 2) * 4;
		CornerY = ((Index >> 1) % 2) * 4;
		CornerZ = ((Index >> 2) % 2) * 4;
		break;
	case 64:
		CornerX = (Index % 4) * 2;
		CornerY = ((Index >> 2) % 4) * 2;
		CornerZ = ((Index >> 4) % 4) * 2;
		break;
	}
	return Cube.CompositePosition(CornerX, CornerY, CornerZ);
}

bool LEDSlidingCube::ThereIsACubePlusX() {
	switch(NumberOfCubes) {
	case 8:
		if ((EmptyIndex == 1) || (EmptyIndex == 3) || (EmptyIndex == 5) || (EmptyIndex == 7)) {
			return false;
		} else {
			return true;
		}
		break;
	case 64:
		if ((EmptyIndex == 3) || (EmptyIndex == 7) || (EmptyIndex == 11) || (EmptyIndex == 15) ||
			(EmptyIndex == 19) || (EmptyIndex == 23) || (EmptyIndex == 27) || (EmptyIndex == 31) ||
			(EmptyIndex == 35) || (EmptyIndex == 39) || (EmptyIndex == 43) || (EmptyIndex == 47) ||
			(EmptyIndex == 51) || (EmptyIndex == 55) || (EmptyIndex == 59) || (EmptyIndex == 63)) {
			return false;
		} else {
			return true;
		}
		break;
	}
}

bool LEDSlidingCube::ThereIsACubeMinusX() {
	switch(NumberOfCubes) {
	case 8:
		if ((EmptyIndex == 0) || (EmptyIndex == 2) || (EmptyIndex == 4) || (EmptyIndex == 6)) {
			return false;
		} else {
			return true;
		}
		break;
	case 64:
		if ((EmptyIndex == 0) || (EmptyIndex == 4) || (EmptyIndex == 8) || (EmptyIndex == 12) ||
			(EmptyIndex == 16) || (EmptyIndex == 20) || (EmptyIndex == 24) || (EmptyIndex == 28) ||
			(EmptyIndex == 32) || (EmptyIndex == 36) || (EmptyIndex == 40) || (EmptyIndex == 44) ||
			(EmptyIndex == 48) || (EmptyIndex == 52) || (EmptyIndex == 56) || (EmptyIndex == 60)) {
			return false;
		} else {
			return true;
		}
		break;
	}
}

bool LEDSlidingCube::ThereIsACubePlusY() {
	switch(NumberOfCubes) {
	case 8:
		if ((EmptyIndex == 2) || (EmptyIndex == 3) || (EmptyIndex == 6) || (EmptyIndex == 7)) {
			return false;
		} else {
			return true;
		}
		break;
	case 64:
		if ((EmptyIndex == 12) || (EmptyIndex == 13) || (EmptyIndex == 14) || (EmptyIndex == 15) ||
			(EmptyIndex == 28) || (EmptyIndex == 29) || (EmptyIndex == 30) || (EmptyIndex == 31) ||
			(EmptyIndex == 44) || (EmptyIndex == 45) || (EmptyIndex == 46) || (EmptyIndex == 47) ||
			(EmptyIndex == 60) || (EmptyIndex == 61) || (EmptyIndex == 62) || (EmptyIndex == 63)) {
			return false;
		} else {
			return true;
		}
		break;
	}
}

bool LEDSlidingCube::ThereIsACubeMinusY() {
	switch(NumberOfCubes) {
	case 8:
		if ((EmptyIndex == 0) || (EmptyIndex == 1) || (EmptyIndex == 4) || (EmptyIndex == 5)) {
			return false;
		} else {
			return true;
		}
		break;
	case 64:
		if ((EmptyIndex == 0) || (EmptyIndex == 1) || (EmptyIndex == 2) || (EmptyIndex == 3) ||
			(EmptyIndex == 16) || (EmptyIndex == 17) || (EmptyIndex == 18) || (EmptyIndex == 19) ||
			(EmptyIndex == 32) || (EmptyIndex == 33) || (EmptyIndex == 34) || (EmptyIndex == 35) ||
			(EmptyIndex == 48) || (EmptyIndex == 49) || (EmptyIndex == 50) || (EmptyIndex == 51)) {
			return false;
		} else {
			return true;
		}
		break;
	}
}

bool LEDSlidingCube::ThereIsACubePlusZ() {
	switch(NumberOfCubes) {
	case 8:
		if ((EmptyIndex == 4) || (EmptyIndex == 5) || (EmptyIndex == 6) || (EmptyIndex == 7)) {
			return false;
		} else {
			return true;
		}
		break;
	case 64:
		if ((EmptyIndex == 48) || (EmptyIndex == 49) || (EmptyIndex == 50) || (EmptyIndex == 51) ||
			(EmptyIndex == 52) || (EmptyIndex == 53) || (EmptyIndex == 54) || (EmptyIndex == 55) ||
			(EmptyIndex == 56) || (EmptyIndex == 57) || (EmptyIndex == 58) || (EmptyIndex == 59) ||
			(EmptyIndex == 60) || (EmptyIndex == 61) || (EmptyIndex == 62) || (EmptyIndex == 63)) {
			return false;
		} else {
			return true;
		}
		break;
	}
}

bool LEDSlidingCube::ThereIsACubeMinusZ() {
	switch(NumberOfCubes) {
	case 8:
		if ((EmptyIndex == 0) || (EmptyIndex == 1) || (EmptyIndex == 2) || (EmptyIndex == 3)) {
			return false;
		} else {
			return true;
		}
		break;
	case 64:
		if ((EmptyIndex == 0) || (EmptyIndex == 1) || (EmptyIndex == 2) || (EmptyIndex == 3) ||
			(EmptyIndex == 4) || (EmptyIndex == 5) || (EmptyIndex == 6) || (EmptyIndex == 7) ||
			(EmptyIndex == 8) || (EmptyIndex == 9) || (EmptyIndex == 10) || (EmptyIndex == 11) ||
			(EmptyIndex == 12) || (EmptyIndex == 13) || (EmptyIndex == 14) || (EmptyIndex == 15)) {
			return false;
		} else {
			return true;
		}
		break;
	}
}
