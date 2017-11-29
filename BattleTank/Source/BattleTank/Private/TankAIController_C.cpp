// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController_C.h"



void ATankAIController_C::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("It's BeginPlay from TankAIController_C"));

	Tank = GetControlledTank();
	FString TankName = Tank->GetName();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIrController Possesses Tank's:  %s"), *TankName);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not Possessess anything"));
}


ATank_C * ATankAIController_C::GetControlledTank() const
{
	return Cast<ATank_C>(GetPawn());
}

