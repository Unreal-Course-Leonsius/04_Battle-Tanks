// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile_C.h"


// Sets default values
AProjectile_C::AProjectile_C()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

