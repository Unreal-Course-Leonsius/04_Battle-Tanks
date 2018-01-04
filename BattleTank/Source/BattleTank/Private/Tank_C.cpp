// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Projectile_C.h"
#include "TankBarrel_C.h"
#include "Tank_C.h"


// Sets default values
ATank_C::ATank_C()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect points as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName ("Aiming Component"));

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
	TankAimingComponent->AimAt(HitLocation, ObjecName, LaunchSpeed);
	//UTankAimingComponent::AimAt(HitLocation, ObjecName); // it's not work because UTankAimingComponent is not it's parent class without inheritnace it wouldn't be call function like this
}

void ATank_C::SetTurretReference(UTankTurret_C * TurretToSet)
{
	if (!TurretToSet) { return; }
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank_C::SetBarrelReference(UTankBarrel_C * BarrelToSet)
{
	if (!BarrelToSet) { return; }
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank_C::Firing()
{
	//UE_LOG(LogTemp, Warning, TEXT("It's Firing... %s"), *ProjectileBlueprint->GetName());

	if (!Barrel) { return; }
	
	// Spawn a projectile at the socket location on the barrel
	auto Projectile = GetWorld()->SpawnActor<AProjectile_C>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))  // it's matching Projectile's ForwardVector
		);


	//UE_LOG(LogTemp, Warning, TEXT("It's Firing... %s"), *Projectile->GetName());
	Projectile->LaunchProjectile(LaunchSpeed);
}



