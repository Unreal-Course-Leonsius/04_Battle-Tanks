// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController_C.generated.h"

// Forward Declaration
class ATank_C;

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

	// returns an OUT parameters true if hit Landscape
	bool GetSightRayHitLocation(FVector&, FString &) const; // aq & = OUT Unrealshi &-it parametris gadacema ais Macros OUT radgan parameter icvleba OUT- mxolod simboluri agnishvnaa

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;
	
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D &, FVector &) const; // tu const functiashi viyenebt sxva functias isic aucileblad unda iyos const

	bool GetLookVectorHitLocation(FVector, FVector &, FString & ) const;
	
};
