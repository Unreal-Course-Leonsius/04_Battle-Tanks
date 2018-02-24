// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret_C.h"



void UTankTurret_C::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	//UE_LOG(LogTemp, Warning, TEXT("Tank Name: %s = %f"), *GetOwner()->GetName(),RawNewRotation);
	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
