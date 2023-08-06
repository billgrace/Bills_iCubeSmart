// LEDChase.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDChase.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDChase Chase;

LEDChase::LEDChase() {

}

int LEDChase::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDChase::StartChase() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Cube.SetAnimationStepSpeedPeriodTo(random(50, 85));
	StepCounter = 0;
	StepTarget = random(200, 800);
	RunnerX = random(0, 7);
	RunnerY = random(0, 7);
	RunnerZ = random(0, 7);
	ChaserX = RunnerX;
	ChaserY = RunnerY;
	ChaserZ = RunnerZ;
	PickNewDirection();
	RunnerRed = Cube.RandomColor();
	RunnerGreen = Cube.RandomColor();
	RunnerBlue = Cube.RandomColor();
	ChaserRed = Cube.RandomColor();
	ChaserGreen = Cube.RandomColor();
	ChaserBlue = Cube.RandomColor();
	DrawRunner(RunnerRed, RunnerGreen, RunnerBlue);
}

void LEDChase::StepChase() {
	// Save runner positions for chaser
	for (int i = 3; i > 0; i--) {
		ChaseDelay[i][0] = ChaseDelay[i-1][0];
		ChaseDelay[i][1] = ChaseDelay[i-1][1];
		ChaseDelay[i][2] = ChaseDelay[i-1][2];
	}
	ChaseDelay[0][0] = RunnerX;
	ChaseDelay[0][1] = RunnerY;
	ChaseDelay[0][2] = RunnerZ;
	// Erase previous runner, move runner, redraw runner
	DrawRunner(0, 0, 0);
	MoveRunner();
	DrawRunner(RunnerRed, RunnerGreen, RunnerBlue);
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartChase();
	}
	// Erase previous chaser, pick up new position from delay array, redraw chaser
	DrawChaser(0, 0, 0);
	ChaserX = ChaseDelay[3][0];
	ChaserY = ChaseDelay[3][1];
	ChaserZ = ChaseDelay[3][2];
	DrawChaser(ChaserRed, ChaserGreen, ChaserBlue);
}

void LEDChase::DrawRunner(int R, int G, int B) {
	Cube.SetLEDColor(RunnerX, RunnerY, RunnerZ, R, G, B);
}

void LEDChase::DrawChaser(int R, int G, int B) {
	Cube.SetLEDColor(ChaserX, ChaserY, ChaserZ, R, G, B);
}

void LEDChase::MoveRunner() {
	if (RunnerDeltaX > 0) {
		if (RunnerX < 7) {
			RunnerX++;
			// return;
		} else {
			PickNewDirection();
			return;
		}
	}
	if (RunnerDeltaX < 0) {
		if (RunnerX > 0) {
			RunnerX--;
			// return;
		} else {
			PickNewDirection();
			return;
		}
	}
	if (RunnerDeltaY > 0) {
		if (RunnerY < 7) {
			RunnerY++;
			// return;
		} else {
			PickNewDirection();
			return;
		}
	}
	if (RunnerDeltaY < 0) {
		if (RunnerY > 0) {
			RunnerY--;
			// return;
		} else {
			PickNewDirection();
			return;
		}
	}
	if (RunnerDeltaZ > 0) {
		if (RunnerZ < 7) {
			RunnerZ++;
			// return;
		} else {
			PickNewDirection();
			return;
		}
	}
	if (RunnerDeltaZ < 0) {
		if (RunnerZ > 0) {
			RunnerZ--;
			// return;
		} else {
			PickNewDirection();
			return;
		}
	}
}

void LEDChase::PickNewDirection() {
	// Start with totally random new direction
	RunnerDeltaX = random(-1, 2);
	RunnerDeltaY = random(-1, 2);
	RunnerDeltaZ = random(-1, 2);
	// Now check positions and constrain directions if needed
	if (RunnerX == 0) {
		// RunnerDeltaX = 1;
		RunnerDeltaX = Cube.RandomPickOfTwo(0, 1);
	}
	if (RunnerX == 7) {
		// RunnerDeltaX = -1;
		RunnerDeltaX = Cube.RandomPickOfTwo(-1, 0);
	}
	if (RunnerY == 0) {
		// RunnerDeltaY = 1;
		RunnerDeltaY = Cube.RandomPickOfTwo(0, 1);
	}
	if (RunnerY == 7) {
		// RunnerDeltaY = -1;
		RunnerDeltaY = Cube.RandomPickOfTwo(-1, 0);
	}
	if (RunnerZ == 0) {
		// RunnerDeltaZ = 1;
		RunnerDeltaZ = Cube.RandomPickOfTwo(0, 1);
	}
	if (RunnerZ == 7) {
		// RunnerDeltaZ = -1;
		RunnerDeltaZ = Cube.RandomPickOfTwo(-1, 0);
	}
	// Finally, make sure we're not stuck with all 3 deltas at zero
	if ((0 == RunnerDeltaX) && (0 == RunnerDeltaY) && (0 == RunnerDeltaZ)) {
		// ... nothing clever, just bail out to some random internal position & direction
		RunnerDeltaX = Cube.RandomPickOfTwo(-1, 1);
		RunnerDeltaY = Cube.RandomPickOfTwo(-1, 1);
		RunnerDeltaZ = Cube.RandomPickOfTwo(-1, 1);
		RunnerX = random(2, 6);
		RunnerY = random(2, 6);
		RunnerZ = random(2, 6);
	}
}
