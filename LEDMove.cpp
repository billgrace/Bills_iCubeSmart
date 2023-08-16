// LEDMove.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"

extern LEDCube Cube;
extern LEDMove Move;

LEDMove::LEDMove() {

}

void LEDMove::InitializeCubeMove(int Radius, int Mode, int SegmentCountTarget) {
	CubeMoveSegmentCounter = 0;
	CubeMoveSegmentTarget = SegmentCountTarget;
	CubeMoveMode = Mode;
	ObjectRadius = Radius;
	switch(Radius) {
	case 1:
		MinPosition = 0;
		MaxPosition = 7;
		break;
	case 2:
		MinPosition = 1;
		MaxPosition = 6;
		break;
	case 3:
		MinPosition = 2;
		MaxPosition = 5;
		break;
	case 4:
		MinPosition = 3;
		MaxPosition = 4;
		break;
	}
	switch (CubeMoveMode) {
	case 0:
		// traverse all edges of the cube
		CurrentCubeSegmentNumber = random(0, 24);
		break;
	case 1:
		// rotate around the edges of an outer X plane
		CurrentCubeSegmentNumber = Cube.RandomPickOfSixteen(1, 2, 4, 5, 6, 8, 9, 11, 12, 14, 15, 17, 18, 19, 21, 22);
		break;
	case 2:
		// rotate around the edges of an outer Y plane
		CurrentCubeSegmentNumber = Cube.RandomPickOfSixteen(0, 2, 3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 20, 21, 23);
		break;
	case 3:
		// rotate around the edges of an outer Z plane
		CurrentCubeSegmentNumber = Cube.RandomPickOfSixteen(0, 1, 3, 4, 6, 7, 9, 10, 13, 14, 16, 17, 19, 20, 22, 23);
		break;
	}
	StartCubeMoveSegment();
}

bool LEDMove::AtEndOfCurrentCubeMoveSegment() {
	switch(CurrentCubeSegmentNumber) {
	case 0:
		if (CurrentCubeMoveX == MaxPosition) return true;
		break;
	case 1:
		if (CurrentCubeMoveY == MaxPosition) return true;
		break;
	case 2:
		if (CurrentCubeMoveZ == MaxPosition) return true;
		break;
	case 3:
		if (CurrentCubeMoveX == MinPosition) return true;
		break;
	case 4:
		if (CurrentCubeMoveY == MaxPosition) return true;
		break;
	case 5:
		if (CurrentCubeMoveZ == MaxPosition) return true;
		break;
	case 6:
		if (CurrentCubeMoveY == MinPosition) return true;
		break;
	case 7:
		if (CurrentCubeMoveX == MaxPosition) return true;
		break;
	case 8:
		if (CurrentCubeMoveZ == MaxPosition) return true;
		break;
	case 9:
		if (CurrentCubeMoveY == MinPosition) return true;
		break;
	case 10:
		if (CurrentCubeMoveX == MinPosition) return true;
		break;
	case 11:
		if (CurrentCubeMoveZ == MaxPosition) return true;
		break;
	case 12:
		if (CurrentCubeMoveZ == MinPosition) return true;
		break;
	case 13:
		if (CurrentCubeMoveX == MaxPosition) return true;
		break;
	case 14:
		if (CurrentCubeMoveY == MaxPosition) return true;
		break;
	case 15:
		if (CurrentCubeMoveZ == MinPosition) return true;
		break;
	case 16:
		if (CurrentCubeMoveX == MinPosition) return true;
		break;
	case 17:
		if (CurrentCubeMoveY == MaxPosition) return true;
		break;
	case 18:
		if (CurrentCubeMoveZ == MinPosition) return true;
		break;
	case 19:
		if (CurrentCubeMoveY == MinPosition) return true;
		break;
	case 20:
		if (CurrentCubeMoveX == MaxPosition) return true;
		break;
	case 21:
		if (CurrentCubeMoveZ == MinPosition) return true;
		break;
	case 22:
		if (CurrentCubeMoveY == MinPosition) return true;
		break;
	case 23:
		if (CurrentCubeMoveX == MinPosition) return true;
		break;
	}
	return false;
}

void LEDMove::AdvanceToNextCubeMovePosition() {
	CurrentCubeMoveX += DeltaX;
	CurrentCubeMoveY += DeltaY;
	CurrentCubeMoveZ += DeltaZ;
}

int LEDMove::GetCurrentCubeMoveX() {
	return CurrentCubeMoveX;
}

int LEDMove::GetCurrentCubeMoveY() {
	return CurrentCubeMoveY;
}

int LEDMove::GetCurrentCubeMoveZ() {
	return CurrentCubeMoveZ;
}

int LEDMove::GetCubeMoveDeltaX() {
	return DeltaX;
}

int LEDMove::GetCubeMoveDeltaY() {
	return DeltaY;
}

int LEDMove::GetCubeMoveDeltaZ() {
	return DeltaZ;
}

void LEDMove::SetupNextCubeMoveSegment() {
	int NewSegmentNumber;
	switch(CubeMoveMode) {
	case 0:
		// traverse all edges of the cube
		switch(CurrentCubeSegmentNumber) {
		case 0:
			NewSegmentNumber = Cube.RandomPickOfTwo(4, 5);
			break;
		case 1:
			NewSegmentNumber = Cube.RandomPickOfTwo(7, 8);
			break;
		case 2:
			NewSegmentNumber = Cube.RandomPickOfTwo(13, 14);
			break;
		case 3:
			NewSegmentNumber = Cube.RandomPickOfTwo(1, 2);
			break;
		case 4:
			NewSegmentNumber = Cube.RandomPickOfTwo(10, 11);
			break;
		case 5:
			NewSegmentNumber = Cube.RandomPickOfTwo(16, 17);
			break;
		case 6:
			NewSegmentNumber = Cube.RandomPickOfTwo(0, 2);
			break;
		case 7:
			NewSegmentNumber = Cube.RandomPickOfTwo(9, 11);
			break;
		case 8:
			NewSegmentNumber = Cube.RandomPickOfTwo(19, 20);
			break;
		case 9:
			NewSegmentNumber = Cube.RandomPickOfTwo(3, 5);
			break;
		case 10:
			NewSegmentNumber = Cube.RandomPickOfTwo(6, 8);
			break;
		case 11:
			NewSegmentNumber = Cube.RandomPickOfTwo(22, 23);
			break;
		case 12:
			NewSegmentNumber = Cube.RandomPickOfTwo(0, 1);
			break;
		case 13:
			NewSegmentNumber = Cube.RandomPickOfTwo(15, 17);
			break;
		case 14:
			NewSegmentNumber = Cube.RandomPickOfTwo(18, 20);
			break;
		case 15:
			NewSegmentNumber = Cube.RandomPickOfTwo(3, 4);
			break;
		case 16:
			NewSegmentNumber = Cube.RandomPickOfTwo(12, 14);
			break;
		case 17:
			NewSegmentNumber = Cube.RandomPickOfTwo(21, 23);
			break;
		case 18:
			NewSegmentNumber = Cube.RandomPickOfTwo(6, 7);
			break;
		case 19:
			NewSegmentNumber = Cube.RandomPickOfTwo(12, 13);
			break;
		case 20:
			NewSegmentNumber = Cube.RandomPickOfTwo(21, 22);
			break;
		case 21:
			NewSegmentNumber = Cube.RandomPickOfTwo(9, 10);
			break;
		case 22:
			NewSegmentNumber = Cube.RandomPickOfTwo(15, 16);
			break;
		case 23:
			NewSegmentNumber = Cube.RandomPickOfTwo(18, 19);
			break;
		}
		break;
	case 1:
		// rotate around the edges of an outer X plane
		CubeMoveSegmentCounter++;
		if (CubeMoveSegmentCounter >= CubeMoveSegmentTarget) {
			CubeMoveSegmentCounter = 0;
			CubeMoveMode = 2;
			NewSegmentNumber = Cube.RandomPickOfSixteen(0, 2, 3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 20, 21, 23);
		} else {
			switch (CurrentCubeSegmentNumber) {
			case 1:
				NewSegmentNumber = 8;
				break;
			case 2:
				NewSegmentNumber = 14;
				break;
			case 4:
				NewSegmentNumber = 11;
				break;
			case 5:
				NewSegmentNumber = 17;
				break;
			case 6:
				NewSegmentNumber = 2;
				break;
			case 8:
				NewSegmentNumber = 19;
				break;
			case 9:
				NewSegmentNumber = 5;
				break;
			case 11:
				NewSegmentNumber = 22;
				break;
			case 12:
				NewSegmentNumber = 1;
				break;
			case 14:
				NewSegmentNumber = 18;
				break;
			case 15:
				NewSegmentNumber = 4;
				break;
			case 17:
				NewSegmentNumber = 21;
				break;
			case 18:
				NewSegmentNumber = 6;
				break;
			case 19:
				NewSegmentNumber = 12;
				break;
			case 21:
				NewSegmentNumber = 9;
				break;
			case 22:
				NewSegmentNumber = 15;
				break;
			default:
				Serial1.print("Invalid CurrentCubeSegmentNumber: ");
				Serial1.print(CurrentCubeSegmentNumber);
				Serial1.println(" in SetupNextCubeMoveSegment() case 1");
				break;
			}
		}
		break;
	case 2:
		// rotate around the edges of an outer Y plane
		CubeMoveSegmentCounter++;
		if (CubeMoveSegmentCounter >= CubeMoveSegmentTarget) {
			CubeMoveSegmentCounter = 0;
			CubeMoveMode = 3;
			NewSegmentNumber = Cube.RandomPickOfSixteen(0, 1, 3, 4, 6, 7, 9, 10, 13, 14, 16, 17, 19, 20, 22, 23);
		} else {
			switch (CurrentCubeSegmentNumber) {
			case 0:
				NewSegmentNumber = 5;
				break;
			case 2:
				NewSegmentNumber = 13;
				break;
			case 3:
				NewSegmentNumber = 2;
				break;
			case 5:
				NewSegmentNumber = 16;
				break;
			case 7:
				NewSegmentNumber = 11;
				break;
			case 8:
				NewSegmentNumber = 20;
				break;
			case 10:
				NewSegmentNumber = 8;
				break;
			case 11:
				NewSegmentNumber = 23;
				break;
			case 12:
				NewSegmentNumber = 0;
				break;
			case 13:
				NewSegmentNumber = 15;
				break;
			case 15:
				NewSegmentNumber = 3;
				break;
			case 16:
				NewSegmentNumber = 12;
				break;
			case 18:
				NewSegmentNumber = 7;
				break;
			case 20:
				NewSegmentNumber = 21;
				break;
			case 21:
				NewSegmentNumber = 10;
				break;
			case 23:
				NewSegmentNumber = 18;
				break;
			default:
				Serial1.print("Invalid CurrentCubeSegmentNumber: ");
				Serial1.print(CurrentCubeSegmentNumber);
				Serial1.println(" in SetupNextCubeMoveSegment() case 2");
				break;
			}
		}
		break;
	case 3:
		// rotate around the edges of an outer Z plane
		CubeMoveSegmentCounter++;
		if (CubeMoveSegmentCounter >= CubeMoveSegmentTarget) {
			CubeMoveSegmentCounter = 0;
			CubeMoveMode = 1;
			NewSegmentNumber = Cube.RandomPickOfSixteen(1, 2, 4, 5, 6, 8, 9, 11, 12, 14, 15, 17, 18, 19, 21, 22);
		} else {
			switch (CurrentCubeSegmentNumber) {
			case 0:
				NewSegmentNumber = 4;
				break;
			case 1:
				NewSegmentNumber = 7;
				break;
			case 3:
				NewSegmentNumber = 1;
				break;
			case 4:
				NewSegmentNumber = 10;
				break;
			case 6:
				NewSegmentNumber = 0;
				break;
			case 7:
				NewSegmentNumber = 9;
				break;
			case 9:
				NewSegmentNumber = 3;
				break;
			case 10:
				NewSegmentNumber = 6;
				break;
			case 13:
				NewSegmentNumber = 17;
				break;
			case 14:
				NewSegmentNumber = 20;
				break;
			case 16:
				NewSegmentNumber = 14;
				break;
			case 17:
				NewSegmentNumber = 23;
				break;
			case 19:
				NewSegmentNumber = 13;
				break;
			case 20:
				NewSegmentNumber = 22;
				break;
			case 22:
				NewSegmentNumber = 16;
				break;
			case 23:
				NewSegmentNumber = 19;
				break;
			default:
				Serial1.print("Invalid CurrentCubeSegmentNumber: ");
				Serial1.print(CurrentCubeSegmentNumber);
				Serial1.println(" in SetupNextCubeMoveSegment() case 3");
				break;
			}
		}
		break;
	}
	CurrentCubeSegmentNumber = NewSegmentNumber;
}

void LEDMove::StartCubeMoveSegment() {
	switch(CurrentCubeSegmentNumber) {
	case 0:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 1:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = 1;
		DeltaZ = 0;
		break;
	case 2:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = 1;
		break;
	case 3:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = -1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 4:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = 1;
		DeltaZ = 0;
		break;
	case 5:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = 1;
		break;
	case 6:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = -1;
		DeltaZ = 0;
		break;
	case 7:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 8:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = 1;
		break;
	case 9:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = -1;
		DeltaZ = 0;
		break;
	case 10:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = -1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 11:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MinPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = 1;
		break;
	case 12:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = -1;
		break;
	case 13:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 14:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = 1;
		DeltaZ = 0;
		break;
	case 15:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = -1;
		break;
	case 16:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = -1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 17:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MinPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = 1;
		DeltaZ = 0;
		break;
	case 18:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = -1;
		break;
	case 19:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = -1;
		DeltaZ = 0;
		break;
	case 20:
		CurrentCubeMoveX = MinPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	case 21:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = 0;
		DeltaZ = -1;
		break;
	case 22:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = 0;
		DeltaY = -1;
		DeltaZ = 0;
		break;
	case 23:
		CurrentCubeMoveX = MaxPosition;
		CurrentCubeMoveY = MaxPosition;
		CurrentCubeMoveZ = MaxPosition;
		DeltaX = -1;
		DeltaY = 0;
		DeltaZ = 0;
		break;
	}
}

int LEDMove::GetSpiralMovePosition0(int Index) {
	return SpiralPositions[CurrentSpiralPattern][Index][0];
}

int LEDMove::GetSpiralMovePosition1(int Index) {
	return SpiralPositions[CurrentSpiralPattern][Index][1];
}

void LEDMove::SetSpiralMovePattern(int Pattern) {
	CurrentSpiralPattern = Pattern;
}

void LEDMove::InitializeHingeMove() {
	// Randomly pick a face as our starting point
	ToFace = random(0, 6);
	// Randomly pick a hinge direction for our first move
	switch (ToFace) {
	case 0:
		CurrentHinge = Cube.RandomPickOfFour(1, 2, 6, 9);
		break;
	case 1:
		CurrentHinge = Cube.RandomPickOfFour(0, 2, 4, 8);
		break;
	case 2:
		CurrentHinge = Cube.RandomPickOfFour(0, 1, 3, 5);
		break;
	case 3:
		CurrentHinge = Cube.RandomPickOfFour(3, 4, 7, 10);
		break;
	case 4:
		CurrentHinge = Cube.RandomPickOfFour(5, 6, 7, 11);
		break;
	case 5:
		CurrentHinge = Cube.RandomPickOfFour(8, 9, 10, 11);
		break;
	}
	SetupNextHingeFace();
}

void LEDMove::SetupNextHingeFace() {
	// Previous ending face is the new starting face
	FromFace = ToFace;
	// Remember previous direction to avoid reflecting back the way we came
	PreviousHinge = CurrentHinge;
	// Pick a new hinge to use for the upcoming motion
	//  ... remembering the previous hinge to avoid re-use
	switch (FromFace) {
	case 0:
		switch (PreviousHinge) {
		case 1:
			CurrentHinge = Cube.RandomPickOfThree(2, 6, 9);
			break;
		case 2:
			CurrentHinge = Cube.RandomPickOfThree(1, 6, 9);
			break;
		case 6:
			CurrentHinge = Cube.RandomPickOfThree(1, 2, 9);
			break;
		case 9:
			CurrentHinge = Cube.RandomPickOfThree(1, 2, 6);
			break;
		default:
			Serial1.print("Bad PreviousHinge: ");
			Serial1.print(PreviousHinge);
			Serial1.print(" - FromFace: ");
			Serial1.print(FromFace);
			Serial1.println(" in SetupNextHingeFace2");
			break;
		}
		// Now set the new target face and the swivel to be used
		switch (CurrentHinge) {
		case 1:
			// Face 0 to 2
			CurrentSwivel = 1;
			ToFace = 2;
			break;
		case 2:
			// Face 0 to 1
			CurrentSwivel = 0;
			ToFace = 1;
			break;
		case 6:
			// Face 0 to 4
			CurrentSwivel = 2;
			ToFace = 4;
			break;
		case 9:
			// Face 0 to 5
			CurrentSwivel = 3;
			ToFace = 5;
			break;
		}
		break;
	case 1:
		switch (PreviousHinge) {
		case 0:
			CurrentHinge = Cube.RandomPickOfThree(2, 4, 8);
			break;
		case 2:
			CurrentHinge = Cube.RandomPickOfThree(0, 4, 8);
			break;
		case 4:
			CurrentHinge = Cube.RandomPickOfThree(0, 2, 8);
			break;
		case 8:
			CurrentHinge = Cube.RandomPickOfThree(0, 2, 4);
			break;
		default:
			Serial1.print("Bad PreviousHinge: ");
			Serial1.print(PreviousHinge);
			Serial1.print(" - FromFace: ");
			Serial1.print(FromFace);
			Serial1.println(" in SetupNextHingeFace2");
			break;
		}
		switch (CurrentHinge) {
		case 0:
			// Face 1 to 2
			CurrentSwivel = 5;
			ToFace = 2;
			break;
		case 2:
			// Face 1 to 0
			CurrentSwivel = 4;
			ToFace = 0;
			break;
		case 4:
			// Face 1 to 3
			CurrentSwivel = 6;
			ToFace = 3;
			break;
		case 8:
			// Face 1 to 5
			CurrentSwivel = 7;
			ToFace = 5;
			break;
		}
		break;
	case 2:
		switch (PreviousHinge) {
		case 0:
			CurrentHinge = Cube.RandomPickOfThree(1, 3, 5);
			break;
		case 1:
			CurrentHinge = Cube.RandomPickOfThree(0, 3, 5);
			break;
		case 3:
			CurrentHinge = Cube.RandomPickOfThree(0, 1, 5);
			break;
		case 5:
			CurrentHinge = Cube.RandomPickOfThree(0, 1, 3);
			break;
		default:
			Serial1.print("Bad PreviousHinge: ");
			Serial1.print(PreviousHinge);
			Serial1.print(" - FromFace: ");
			Serial1.print(FromFace);
			Serial1.println(" in SetupNextHingeFace2");
			break;
		}
		switch (CurrentHinge) {
		case 0:
			// Face 2 to 1
			CurrentSwivel = 9;
			ToFace = 1;
			break;
		case 1:
			// Face 2 to 0
			CurrentSwivel = 8;
			ToFace = 0;
			break;
		case 3:
			// Face 2 to 3
			CurrentSwivel = 10;
			ToFace = 3;
			break;
		case 5:
			// Face 2 to 4
			CurrentSwivel = 11;
			ToFace = 4;
			break;
		}
		break;
	case 3:
		switch (PreviousHinge) {
		case 3:
			CurrentHinge = Cube.RandomPickOfThree(4, 7, 10);
			break;
		case 4:
			CurrentHinge = Cube.RandomPickOfThree(3, 7, 10);
			break;
		case 7:
			CurrentHinge = Cube.RandomPickOfThree(3, 4, 10);
			break;
		case 10:
			CurrentHinge = Cube.RandomPickOfThree(3, 4, 7);
			break;
		default:
			Serial1.print("Bad PreviousHinge: ");
			Serial1.print(PreviousHinge);
			Serial1.print(" - FromFace: ");
			Serial1.print(FromFace);
			Serial1.println(" in SetupNextHingeFace2");
			break;
		}
		switch (CurrentHinge) {
		case 3:
			// Face 3 to 2
			CurrentSwivel = 13;
			ToFace = 2;
			break;
		case 4:
			// Face 3 to 1
			CurrentSwivel = 12;
			ToFace = 1;
			break;
		case 7:
			// Face 3 to 4
			CurrentSwivel = 14;
			ToFace = 4;
			break;
		case 10:
			// Face 3 to 5
			CurrentSwivel = 15;
			ToFace = 5;
			break;
		}
		break;
	case 4:
		switch (PreviousHinge) {
		case 5:
			CurrentHinge = Cube.RandomPickOfThree(6, 7, 11);
			break;
		case 6:
			CurrentHinge = Cube.RandomPickOfThree(5, 7, 11);
			break;
		case 7:
			CurrentHinge = Cube.RandomPickOfThree(5, 6, 11);
			break;
		case 11:
			CurrentHinge = Cube.RandomPickOfThree(5, 6, 7);
			break;
		default:
			Serial1.print("Bad PreviousHinge: ");
			Serial1.print(PreviousHinge);
			Serial1.print(" - FromFace: ");
			Serial1.print(FromFace);
			Serial1.println(" in SetupNextHingeFace2");
			break;
		}
		switch (CurrentHinge) {
		case 5:
			// Face 4 to 2
			CurrentSwivel = 17;
			ToFace = 2;
			break;
		case 6:
			// Face 4 to 0
			CurrentSwivel = 16;
			ToFace = 0;
			break;
		case 7:
			// Face 4 to 3
			CurrentSwivel = 18;
			ToFace = 3;
			break;
		case 11:
			// Face 4 to 5
			CurrentSwivel = 19;
			ToFace = 5;
			break;
		}
		break;
	case 5:
		switch (PreviousHinge) {
		case 8:
			CurrentHinge = Cube.RandomPickOfThree(9, 10, 11);
			break;
		case 9:
			CurrentHinge = Cube.RandomPickOfThree(8, 10, 11);
			break;
		case 10:
			CurrentHinge = Cube.RandomPickOfThree(8, 9, 11);
			break;
		case 11:
			CurrentHinge = Cube.RandomPickOfThree(8, 9, 10);
			break;
		default:
			Serial1.print("Bad PreviousHinge: ");
			Serial1.print(PreviousHinge);
			Serial1.print(" - FromFace: ");
			Serial1.print(FromFace);
			Serial1.println(" in SetupNextHingeFace2");
			break;
		}
		switch (CurrentHinge) {
		case 8:
			// Face 5 to 1
			CurrentSwivel = 21;
			ToFace = 1;
			break;
		case 9:
			// Face 5 to 0
			CurrentSwivel = 20;
			ToFace = 0;
			break;
		case 10:
			// Face 5 to 3
			CurrentSwivel = 22;
			ToFace = 3;
			break;
		case 11:
			// Face 5 to 4
			CurrentSwivel = 23;
			ToFace = 4;
			break;
		}
		break;
	}
}

int LEDMove::GetCurrentSwivel() {
	return CurrentSwivel;
}

int LEDMove::GetHingePosition0(int Angle, int Index) {
	return HingePositions[Angle][Index][0];
}

int LEDMove::GetHingePosition1(int Angle, int Index) {
	return HingePositions[Angle][Index][1];
}

void LEDMove::InitializePongMove(int Radius) {
	ObjectRadius = Radius;
	switch(Radius) {
	case 1:
		MinPosition = 0;
		MaxPosition = 7;
		break;
	case 2:
		MinPosition = 1;
		MaxPosition = 6;
		break;
	case 3:
		MinPosition = 2;
		MaxPosition = 5;
		break;
	case 4:
		MinPosition = 3;
		MaxPosition = 4;
		break;
	}
	CurrentPongMoveX = random(MinPosition, MaxPosition + 1);
	CurrentPongMoveY = random(MinPosition, MaxPosition + 1);
	CurrentPongMoveZ = random(MinPosition, MaxPosition + 1);
	DeltaX = Cube.RandomPickOfTwo(-1, 1);
	DeltaY = Cube.RandomPickOfTwo(-1, 1);
	DeltaZ = Cube.RandomPickOfTwo(-1, 1);
}

void LEDMove::StepPongMove() {
	NewX = CurrentPongMoveX + DeltaX;
	if (NewX > MaxPosition) {
		DeltaX = -DeltaX;
		NewX = MaxPosition - 1;
	}
	if (NewX < MinPosition) {
		DeltaX = -DeltaX;
		NewX = MinPosition + 1;
	}
	NewY = CurrentPongMoveY + DeltaY;
	if (NewY > MaxPosition) {
		DeltaY = -DeltaY;
		NewY = MaxPosition - 1;
	}
	if (NewY < MinPosition) {
		DeltaY = -DeltaY;
		NewY = MinPosition + 1;
	}
	NewZ = CurrentPongMoveZ + DeltaZ;
	if (NewZ > MaxPosition) {
		DeltaZ = -DeltaZ;
		NewZ = MaxPosition - 1;
	}
	if (NewZ < MinPosition) {
		DeltaZ = -DeltaZ;
		NewZ = MinPosition + 1;
	}
	CurrentPongMoveX = NewX;
	CurrentPongMoveY = NewY;
	CurrentPongMoveZ = NewZ;
}

int LEDMove::GetCurrentPongMoveX() {
	return CurrentPongMoveX;
}

int LEDMove::GetCurrentPongMoveY() {
	return CurrentPongMoveY;
}

int LEDMove::GetCurrentPongMoveZ(){
	return CurrentPongMoveZ;
}


void LEDMove::InitializeSloshMove() {
	SloshIndex = 0;
}

void LEDMove::StepSloshMove() {
	SloshIndex = Cube.NextIndex(SloshIndex, SloshMoveIndexCount);
}

int LEDMove::GetSloshX() {
	return SloshPositionsAndSpeeds[SloshIndex][0];
}

int LEDMove::GetSloshZ() {
	return SloshPositionsAndSpeeds[SloshIndex][1];
}

int LEDMove::GetSloshM() {
	return SloshPositionsAndSpeeds[SloshIndex][2];
}

bool LEDMove::SloshIsAtBeginning() {
	if (SloshIndex == 0) {
		return true;
	} else {
		return false;
	}
}

bool LEDMove::SloshIsAtEnd() {
	if (SloshIndex == (SloshMoveIndexCount - 1)) {
		return true;
	} else {
		return false;
	}
}

int LEDMove::GetRotorMoveX(int Angle, int BarPoint) {
	return RotorMoveBarCoordinates[Angle][BarPoint][0];
}
int LEDMove::GetRotorMoveY(int Angle, int BarPoint) {
	return RotorMoveBarCoordinates[Angle][BarPoint][1];
}

int LEDMove::GetCircleMoveX(int Angle) {
	return CircleMovePositions[Angle][0];
}

int LEDMove::GetCircleMoveY(int Angle) {
	return CircleMovePositions[Angle][1];
}

void LEDMove::InitializeMerryGoRoundMove(int EdgeSize) {
	MerryGoRoundMaxCoordinate = 8 - EdgeSize;
	MerryGoRoundMoveEdgeSize = EdgeSize;
	MerryGoRoundCurrentDirection = random(0, 8);
	switch (MerryGoRoundCurrentDirection) {
	case 0:
		// +X @ Y=0
		MerryGoRoundMoveX = 0;
		MerryGoRoundMoveY = 0;
		break;
	case 1:
		// +Y @ X=Max
		MerryGoRoundMoveX = MerryGoRoundMaxCoordinate;
		MerryGoRoundMoveY = 0;
		break;
	case 2:
		// -X @ Y=Max
		MerryGoRoundMoveX = MerryGoRoundMaxCoordinate;
		MerryGoRoundMoveY = MerryGoRoundMaxCoordinate;
		break;
	case 3:
		// -Y @ X=0
		MerryGoRoundMoveX = 0;
		MerryGoRoundMoveY = MerryGoRoundMaxCoordinate;
		break;
	case 4:
		// -X @ Y=0
		MerryGoRoundMoveX = MerryGoRoundMaxCoordinate;
		MerryGoRoundMoveY = 0;
		break;
	case 5:
		// +Y @ X=0
		MerryGoRoundMoveX = 0;
		MerryGoRoundMoveY = 0;
		break;
	case 6:
		// +X @ Y=Max
		MerryGoRoundMoveX = 0;
		MerryGoRoundMoveY = MerryGoRoundMaxCoordinate;
		break;
	case 7:
		// -Y @ X=Max
		MerryGoRoundMoveX = MerryGoRoundMaxCoordinate;
		MerryGoRoundMoveY = MerryGoRoundMaxCoordinate;
		break;
	}
}

void LEDMove::StepMerryGoRoundMove() {
	switch (MerryGoRoundCurrentDirection) {
	case 0:
		// +X @ Y=0
		// Tentatively move right
		MerryGoRoundMoveX++;
		if (MerryGoRoundMoveX > MerryGoRoundMaxCoordinate) {
			// We went too far => it's time to change direction
			MerryGoRoundCurrentDirection = 1;
			// Undo the tentative move to the right
			MerryGoRoundMoveX--;
			// Move in the new direction
			MerryGoRoundMoveY++;
		}
		break;
	case 1:
		// +Y @ X=Max
		MerryGoRoundMoveY++;
		if (MerryGoRoundMoveY > MerryGoRoundMaxCoordinate) {
			MerryGoRoundCurrentDirection = 2;
			MerryGoRoundMoveX--;
			MerryGoRoundMoveY--;
		}
		break;
	case 2:
		// -X @ Y=Max
		MerryGoRoundMoveX--;
		if (MerryGoRoundMoveX < 0) {
			MerryGoRoundCurrentDirection = 3;
			MerryGoRoundMoveX++;
			MerryGoRoundMoveY--;
		}
		break;
	case 3:
		// -Y @ X=0
		MerryGoRoundMoveY--;
		if (MerryGoRoundMoveY < 0) {
			MerryGoRoundCurrentDirection = 0;
			MerryGoRoundMoveX++;
			MerryGoRoundMoveY++;
		}
		break;
	case 4:
		// -X @ Y=0
		MerryGoRoundMoveX--;
		if (MerryGoRoundMoveX < 0) {
			MerryGoRoundCurrentDirection = 5;
			MerryGoRoundMoveX++;
			MerryGoRoundMoveY++;
		}
		break;
	case 5:
		// +Y @ X=0
		MerryGoRoundMoveY++;
		if (MerryGoRoundMoveY > MerryGoRoundMaxCoordinate) {
			MerryGoRoundCurrentDirection = 6;
			MerryGoRoundMoveX++;
			MerryGoRoundMoveY--;
		}
		break;
	case 6:
		// +X @ Y=Max
		MerryGoRoundMoveX++;
		if (MerryGoRoundMoveX > MerryGoRoundMaxCoordinate) {
			MerryGoRoundCurrentDirection = 7;
			MerryGoRoundMoveX--;
			MerryGoRoundMoveY--;
		}
		break;
	case 7:
		// -Y @ X=Max
		MerryGoRoundMoveY--;
		if (MerryGoRoundMoveY < 0) {
			MerryGoRoundCurrentDirection = 4;
			MerryGoRoundMoveX--;
			MerryGoRoundMoveY++;
		}
		break;
	}
}

int LEDMove::GetMerryGoRoundMoveX(){
	return MerryGoRoundMoveX;
}

int LEDMove::GetMerryGoRoundMoveY() {
	return MerryGoRoundMoveY;
}

void LEDMove::InitializeMarathonMove() {
	MarathonMoveX = 0;
	MarathonMoveY = 0;
	MarathonMoveZ = 0;
	MarathonMoveSegment = 0;
	MarathonMoveVerticalDirection = 1;
}

void LEDMove::StepMarathonMove() {
	switch (MarathonMoveSegment) {
	case 0:
		// Moving +X at Y = 0
		MarathonMoveX++;
		if (MarathonMoveX > 7) {
			MarathonMoveX = 7;
			MarathonMoveY = 1;
			MarathonMoveSegment = 1;
		}
		break;
	case 1:
		// Moving +Y at X = 7
		MarathonMoveY++;
		if (MarathonMoveY > 7) {
			MarathonMoveY = 7;
			MarathonMoveX = 6;
			MarathonMoveSegment = 2;
		}
		break;
	case 2:
		// Moving -X at Y = 7
		MarathonMoveX--;
		if (MarathonMoveX < 0) {
			MarathonMoveX = 0;
			MarathonMoveY = 6;
			MarathonMoveSegment = 3;
		}
		break;
	case 3:
		// Moving -Y at X = 0
		MarathonMoveY--;
		if (MarathonMoveY < 0) {
			MarathonMoveY = 0;
			MarathonMoveX = 1;
			MarathonMoveSegment = 0;
			switch (MarathonMoveVerticalDirection) {
			case 1:
				// Presently going up
				MarathonMoveZ++;
				if (MarathonMoveZ > 7) {
					// Went too far, head back down
					MarathonMoveZ = 6;
					MarathonMoveVerticalDirection = -1;
				}
				break;
			case -1:
				// Presently going down
				MarathonMoveZ--;
				if (MarathonMoveZ < 0) {
					// Went too far, head back up
					MarathonMoveZ = 1;
					MarathonMoveVerticalDirection = 1;
				}
				break;
			}
		}
		break;
	}
}


int LEDMove::GetMarathonMoveX() {
	return MarathonMoveX;
}

int LEDMove::GetMarathonMoveY() {
	return MarathonMoveY;
}

int LEDMove::GetMarathonMoveZ() {
	return MarathonMoveZ;
}

int LEDMove::GetSprinklerArcPosition0(int DropNumber) {
	return SprinklerArcPosition[DropNumber][0];
}

int LEDMove::GetSprinklerArcPosition1(int DropNumber) {
	return SprinklerArcPosition[DropNumber][1];
}

int LEDMove::GetCylinderMovePosition0(int Angle, int Radius) {
	return CylinderMovePosition[Angle][Radius][0];
}

int LEDMove::GetCylinderMovePosition1(int Angle, int Radius) {
	return CylinderMovePosition[Angle][Radius][1];
}

