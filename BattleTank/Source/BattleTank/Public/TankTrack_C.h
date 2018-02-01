// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack_C.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to the Tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack_C : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set the Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TankMaxDrivingForce = 40000000.0;
	
};
