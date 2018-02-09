// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
//#include "Tank_C.h"
#include "TankAIController_C.h"



void ATankAIController_C::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("It's BeginPlay from TankAIController_C"));

	
}


void ATankAIController_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	//UE_LOG(LogTemp, Error, TEXT("DONKY %s"), *PlayerTank->GetName());
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank) || !ensure(ControlledTank)) { return; }

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	
	// Move towards the Player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation(), ControlledTank->GetName());
	AimingComponent->Firing();
	
}

/*ATank_C * ATankAIController_C::GetControlledTank() const
{
	return Cast<ATank_C>(GetPawn());
}*/

/*ATank_C * ATankAIController_C::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank_C>(PlayerPawn);
}*/

