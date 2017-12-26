// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel_C.h"


void UTankBarrel_C::Elevate(float RelativeSpeed)
{

	// Move the barrel the right amount this frame

	RelativeSpeed  = FMath::Clamp<float>(RelativeSpeed, -1, +1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	// Given a max elevation speed and the frame time

	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees); // it can use also like FMath::Clamp() without <>

	SetRelativeRotation(FRotator(Elevation,0,0));
	//UE_LOG(LogTemp, Error, TEXT("%f ElevationChange: "), ElevationChange);

}


