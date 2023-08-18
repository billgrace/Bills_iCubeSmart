// LEDSonar.cpp

#include <Arduino.h>
#include "LEDCube.h"
#include "LEDMove.h"
#include "LEDSonar.h"

extern LEDCube Cube;
extern LEDMove Move;
extern LEDSonar Sonar;

LEDSonar::LEDSonar() {

}

int LEDSonar::SuggestedNumberOfAnimationCycles() {
	return 1;
}

void LEDSonar::StartSonar() {
	Cube.ClearImage();
	Cube.IncrementAnimationDurationCycleCount();
	StepCounter = 0;
	StepTarget = random(100, 500);
	Cube.SetAnimationStepSpeedPeriodTo(random(30, 80));
	StartCounter = 0;
	StartTarget = random(2, 5);
	for (int Index = 0; Index < MaxNumberOfSonarBlips; Index++) {
		SonarBlip[Index][6] = 7;
	}
}

void LEDSonar::StepSonar() {
	StepCounter++;
	if (StepCounter >= StepTarget) {
		StepCounter = 0;
		StartSonar();
	}
	StartCounter++;
	if (StartCounter >= StartTarget) {
		StartCounter = 0;
		StartNewBlip();
	}
	StepAllActiveBlips();
}

void LEDSonar::StartNewBlip() {
	// Find an available blip
	bool FoundABlip = false;
	int BlipIndex = 0;
	int NewCompositeColor = 0;
	while ((BlipIndex < MaxNumberOfSonarBlips) && (false == FoundABlip)) {
		// Is this blip available?
		if (SonarBlip[BlipIndex][6] == 7) {
			// then set it to "starting"
			SonarBlip[BlipIndex][6] = 0;
			SonarBlip[BlipIndex][0] = random(1, 7);
			SonarBlip[BlipIndex][1] = random(1, 7);
			SonarBlip[BlipIndex][2] = random(1, 7);
			NewCompositeColor = Cube.RandomSolidColor();
			SonarBlip[BlipIndex][3] = Cube.RedPartOf(NewCompositeColor);
			SonarBlip[BlipIndex][4] = Cube.GreenPartOf(NewCompositeColor);
			SonarBlip[BlipIndex][5] = Cube.BluePartOf(NewCompositeColor);
			FoundABlip = true;
		}
		BlipIndex++;
	}
}

void LEDSonar::StepAllActiveBlips() {
	int X;
	int Y;
	int Z;
	int Red;
	int Green;
	int Blue;
	for (int Index = 0; Index < MaxNumberOfSonarBlips; Index++) {
		X = SonarBlip[Index][0];
		Y = SonarBlip[Index][1];
		Z = SonarBlip[Index][2];
		Red = SonarBlip[Index][3];
		Green = SonarBlip[Index][4];
		Blue = SonarBlip[Index][5];
		switch (SonarBlip[Index][6]) {
		case 0:
			// Center only, attenuation 0
			DrawCenter(X, Y, Z, Red, Green, Blue, 0);
			break;
		case 1:
			// Center only, attenuation 1
			DrawCenter(X, Y, Z, Red, Green, Blue, 1);
			break;
		case 2:
			// Center plus shell 1, attenuation 2
			DrawCenter(X, Y, Z, Red, Green, Blue, 2);
			DrawShell1(X, Y, Z, Red, Green, Blue, 2);
			break;
		case 3:
			// Center plus shell 1, attenuation 3
			DrawCenter(X, Y, Z, Red, Green, Blue, 3);
			DrawShell1(X, Y, Z, Red, Green, Blue, 3);
			break;
		case 4:
			// Shell 1, attenuation 4 (erase center)
			DrawCenter(X, Y, Z, Red, Green, Blue, 7);
			DrawShell1(X, Y, Z, Red, Green, Blue, 4);
			break;
		case 5:
			// Shell 2, attenuation 5
			DrawShell1(X, Y, Z, Red, Green, Blue, 5);
			DrawShell2(X, Y, Z, Red, Green, Blue, 5);
			break;
		case 6:
			// Shell 2, attenuation 6 (erase shell 1)
			DrawShell1(X, Y, Z, Red, Green, Blue, 7);
			DrawShell2(X, Y, Z, Red, Green, Blue, 6);
			break;
		case 7:
			// Erase shell 2 & set to inactive state
			DrawShell2(X, Y, Z, Red, Green, Blue, 7);
			break;
		}
		// If this blip is active, move it to the next state
		if (SonarBlip[Index][6] < 7) {
			SonarBlip[Index][6]++;
		}
	}
}

void LEDSonar::DrawCenter(int X, int Y, int Z, int Red, int Green, int Blue, int Attenuation) {
	int R = Red - Attenuation;
	int G = Green - Attenuation;
	int B = Blue - Attenuation;
	Cube.SetLEDColor(X, Y, Z, R, G, B);
}

void LEDSonar::DrawShell1(int X, int Y, int Z, int Red, int Green, int Blue, int Attenuation) {
	int R = Red - Attenuation;
	int G = Green - Attenuation;
	int B = Blue - Attenuation;
	Cube.SetLEDColor(X+1, Y, Z, R, G, B);
	Cube.SetLEDColor(X-1, Y, Z, R, G, B);
	Cube.SetLEDColor(X, Y+1, Z, R, G, B);
	Cube.SetLEDColor(X, Y-1, Z, R, G, B);
	Cube.SetLEDColor(X, Y, Z+1, R, G, B);
	Cube.SetLEDColor(X, Y, Z-1, R, G, B);
}

void LEDSonar::DrawShell2(int X, int Y, int Z, int Red, int Green, int Blue, int Attenuation) {
	int R = Red - Attenuation;
	int G = Green - Attenuation;
	int B = Blue - Attenuation;
	Cube.SetLEDColor(X+1, Y+1, Z+1, R, G, B);
	Cube.SetLEDColor(X-1, Y+1, Z+1, R, G, B);
	Cube.SetLEDColor(X+1, Y-1, Z+1, R, G, B);
	Cube.SetLEDColor(X-1, Y-1, Z+1, R, G, B);
	Cube.SetLEDColor(X+1, Y+1, Z-1, R, G, B);
	Cube.SetLEDColor(X-1, Y+1, Z-1, R, G, B);
	Cube.SetLEDColor(X+1, Y-1, Z-1, R, G, B);
	Cube.SetLEDColor(X-1, Y-1, Z-1, R, G, B);
}

