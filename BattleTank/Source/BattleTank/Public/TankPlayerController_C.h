// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank_C.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController_C.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController_C : public APlayerController
{
	GENERATED_BODY()

	    
	   virtual void Tick(float DeltaTime) override;

	   virtual void BeginPlay() override;

private:

	AActor* Tank = nullptr;  // It's possible ATank_C* reference

	ATank_C* GetControlledTank() const;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardCrosshair();
	
};
