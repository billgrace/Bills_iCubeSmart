// LEDPool.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDPool.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDPool Pool;

#define MaxPoolHeight 5

LEDPool::LEDPool() {

}

int LEDPool::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDPool::StartPool() {
	Cube.SetAnimationStepSpeedPeriodTo(random(150, 200));
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	Colors[0][0] = Cube.RandomColor();
	Colors[0][1] = Cube.RandomColor();
	Colors[0][2] = Cube.RandomColor();
	Colors[1][0] = Cube.RandomColor();
	Colors[1][1] = Cube.RandomColor();
	Colors[1][2] = Cube.RandomColor();
	Colors[2][0] = Cube.RandomColor();
	Colors[2][1] = Cube.RandomColor();
	Colors[2][2] = Cube.RandomColor();
	Colors[3][0] = Cube.RandomColor();
	Colors[3][1] = Cube.RandomColor();
	Colors[3][2] = Cube.RandomColor();
	StepCounter = 0;
	StepTarget = random(100, 200);
	PoolHeight = random(3, MaxPoolHeight + 1);
	PoolHeightCounter = 0;
	PoolHeightTarget = StepTarget / PoolHeight;
	DrawCornerPool(0);
	DrawCornerPool(1);
	DrawCornerPool(2);
	DrawCornerPool(3);
	DrippingCorner = 0;
	ArcLength = 0;
}

void LEDPool::StepPool() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StartPool();
	}
	DrawArcs(false);
	PoolHeightCounter++;
	if ((PoolHeightCounter >= PoolHeightTarget) && (PoolHeight > 1)) {
		PoolHeightCounter = 0;
		PoolHeight--;
		DrawCornerPool(0);
		DrawCornerPool(1);
		DrawCornerPool(2);
		DrawCornerPool(3);
	}
	DrippingCorner = Cube.NextIndex(DrippingCorner, 4);
	if (ArcLength < 14) ArcLength++;
	DrawArcs(true);
}

void LEDPool::DrawCornerPool(int Corner) {
	int MinX;
	int MaxX;
	int MinY;
	int MaxY;
	int BlankX;
	int BlankY;
	switch(Corner) {
	case 0:
		MinX = 0;
		MaxX = 2;
		MinY = 0;
		MaxY = 2;
		BlankX = 2;
		BlankY = 2;
		break;
	case 1:
		MinX = 5;
		MaxX = 7;
		MinY = 0;
		MaxY = 2;
		BlankX = 5;
		BlankY = 2;
		break;
	case 2:
		MinX = 5;
		MaxX = 7;
		MinY = 5;
		MaxY = 7;
		BlankX = 5;
		BlankY = 5;
		break;
	case 3:
		MinX = 0;
		MaxX = 2;
		MinY = 5;
		MaxY = 7;
		BlankX = 2;
		BlankY = 5;
		break;
	}
	for (int Z = 0; Z < MaxPoolHeight; Z++) {
		for (int X = MinX; X <= MaxX; X++) {
			for (int Y = MinY; Y <= MaxY; Y++) {
				if (Z >= PoolHeight) {
					Cube.SetLEDColor(X, Y, Z, 0, 0, 0);
				} else {
					Cube.SetLEDColor(X, Y, Z, Colors[Corner][0], Colors[Corner][1], Colors[Corner][2]);
				}
			}
		}
		Cube.SetLEDColor(BlankX, BlankY, Z, 0, 0, 0);
	}
}

void LEDPool::DrawArcs(bool OffOn) {
	int Corner0X;
	int Corner0Y;
	int Corner1X;
	int Corner1Y;
	int Corner2X;
	int Corner2Y;
	int Corner3X;
	int Corner3Y;
	int ArcX;
	int ArcY;
	int ArcZ;
	int ArcRed;
	int ArcGreen;
	int ArcBlue;
	int CurrentArcPoint = 0;
	while (CurrentArcPoint <= ArcLength) {
		Corner0X = ArcPoints[CurrentArcPoint][0];
		Corner0Y = ArcPoints[CurrentArcPoint][1];
		ArcZ = ArcPoints[CurrentArcPoint][2];
		Corner1X = 7 - Corner0X;
		Corner1Y = Corner0Y;
		Corner2X = 7 - Corner0X;
		Corner2Y = 7 - Corner0Y;
		Corner3X = Corner0X;
		Corner3Y = 7 - Corner0Y;
		if ((CurrentArcPoint % 4) == DrippingCorner) {
			ArcX = Corner0X;
			ArcY = Corner0Y;
			ArcRed = Colors[0][0];
			ArcGreen = Colors[0][1];
			ArcBlue = Colors[0][2];
		}
		if (((CurrentArcPoint + 1) % 4) == DrippingCorner) {
			ArcX = Corner1X;
			ArcY = Corner1Y;
			ArcRed = Colors[1][0];
			ArcGreen = Colors[1][1];
			ArcBlue = Colors[1][2];
		}
		if (((CurrentArcPoint + 2) % 4) == DrippingCorner) {
			ArcX = Corner2X;
			ArcY = Corner2Y;
			ArcRed = Colors[2][0];
			ArcGreen = Colors[2][1];
			ArcBlue = Colors[2][2];
		}
		if (((CurrentArcPoint + 3) % 4) == DrippingCorner) {
			ArcX = Corner3X;
			ArcY = Corner3Y;
			ArcRed = Colors[3][0];
			ArcGreen = Colors[3][1];
			ArcBlue = Colors[3][2];
		}
		if (OffOn) {
			Cube.SetLEDColor(ArcX, ArcY, ArcZ, ArcRed, ArcGreen, ArcBlue);
		} else {
			Cube.SetLEDColor(ArcX, ArcY, ArcZ, 0, 0, 0);
		}
		CurrentArcPoint++;
	}
	if (ArcLength >= 14) {
		switch((DrippingCorner + 2) % 4) {
		case 0:
			DrawCenterPool(Colors[0][0], Colors[0][1], Colors[0][02]);
			break;
		case 1:
			DrawCenterPool(Colors[1][0], Colors[1][1], Colors[1][02]);
			break;
		case 2:
			DrawCenterPool(Colors[2][0], Colors[2][1], Colors[2][02]);
			break;
		case 3:
			DrawCenterPool(Colors[3][0], Colors[3][1], Colors[3][02]);
			break;
		}
	}
}

void LEDPool::DrawCenterPool(int Red, int Green, int Blue) {
	Cube.SetLEDColor(3, 3, 0, Red, Green, Blue);
	Cube.SetLEDColor(3, 4, 0, Red, Green, Blue);
	Cube.SetLEDColor(4, 3, 0, Red, Green, Blue);
	Cube.SetLEDColor(4, 4, 0, Red, Green, Blue);
}
