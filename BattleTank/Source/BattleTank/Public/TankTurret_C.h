// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret_C.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret_C : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void Rotate(float );

private:

	UPROPERTY(EditAnywhere, Category = "Setup") 
	float MaxDegreesPerSecond = 25;
	
	
	
};
