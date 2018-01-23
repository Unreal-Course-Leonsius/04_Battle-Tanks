// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank_C.h"
#include "TankAIController_C.h"



void ATankAIController_C::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("It's BeginPlay from TankAIController_C"));

	
	FString TankName = GetControlledTank()->GetName();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIrController found Tank:  %s"), *TankName);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not find"));
}


void ATankAIController_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// Move towards the Player
		MoveToActor(GetPlayerTank(), AcceptanceRadius);


		// Aim towards the Player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation(), GetPlayerTank()->GetName());
		//GetControlledTank()->Firing();
	}
}

ATank_C * ATankAIController_C::GetControlledTank() const
{
	return Cast<ATank_C>(GetPawn());
}

ATank_C * ATankAIController_C::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank_C>(PlayerPawn);
}

