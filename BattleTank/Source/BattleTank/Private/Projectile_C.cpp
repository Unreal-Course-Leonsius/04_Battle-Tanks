// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile_C.h"


// Sets default values
AProjectile_C::AProjectile_C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false; // It's responsible not be activeted while there will not be relevant order
}

// Called when the game starts or when spawned
void AProjectile_C::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile_C::LaunchProjectile(float speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed); // ForwardVector is the same as Barrel SocketRotation's Look direction thats why we need not calculat this parameter
	ProjectileMovement->Activate();  // we need it anywhere will be or not bAutoActivate = false. It's responsible moving
}

