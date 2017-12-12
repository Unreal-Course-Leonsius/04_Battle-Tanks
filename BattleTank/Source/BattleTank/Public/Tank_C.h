// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank_C.generated.h"

UCLASS()
class BATTLETANK_API ATank_C : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank_C();

public:	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector, FString);
	
};
