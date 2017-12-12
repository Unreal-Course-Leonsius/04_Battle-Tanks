// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank_C.h"


// Sets default values
ATank_C::ATank_C()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATank_C::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank_C::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank_C::AimAt(FVector HitLocation, FString ObjecName)
{
	auto OurTankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming %s Object Name %s"), *OurTankName, *HitLocation.ToString(), *ObjecName);
}

