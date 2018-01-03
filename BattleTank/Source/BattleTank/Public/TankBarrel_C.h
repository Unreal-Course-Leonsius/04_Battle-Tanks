// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel_C.generated.h"

/**
 * 
 */

UCLASS( meta = (BlueprintSpawnableComponent)) // hidecategories = "Collision"
class BATTLETANK_API UTankBarrel_C : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Elevate(float);
	
private:

	UPROPERTY(EditAnywhere, Category = Setup) // Category = Setup this means that this data will be in Setup Category Group
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;

};
