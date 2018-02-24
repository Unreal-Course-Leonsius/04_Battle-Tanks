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

	/// EditAnywhere = we can change its value as in Blueprint as in Instance properties (Detail) therefor each inscatnce would have different value
	/// EditDefaultsOnly  = we can chagne its value only in Blueprint therefor all instance would have only one value.
	UPROPERTY(EditDefaultsOnly, Category = "Setup") // Category = Setup this means that this data will be in Setup Category Group
	float MaxDegreesPerSecond = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = 0;

};
