// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController_C.h"


void ATankPlayerController_C::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("It's BeginPlay from TankPlayerController_C"));

    Tank = GetControlledTank();
	FString TankName = Tank->GetName();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Possesses Tank's:  %s"),*TankName);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not Possessess anything")); 
}

void ATankPlayerController_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("It's TankPlayrController Ticking..."));
}

ATank_C * ATankPlayerController_C::GetControlledTank() const
{
	return Cast<ATank_C>(GetPawn());
}

void ATankPlayerController_C::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	// Get World location if linetrace through corsshair
	// If it hits the landscape
	  // Tell controlled tank to aim at this point
}
