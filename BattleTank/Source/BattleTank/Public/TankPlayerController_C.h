// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController_C.generated.h"

// Forward Declaration
//class ATank_C;
class UTankAimingComponent;

/**
 * Responsible for helping Player to Aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController_C : public APlayerController
{
	GENERATED_BODY()

	    
	   virtual void Tick(float DeltaTime) override;

	   virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FindAimingComponent(UTankAimingComponent *AimCompRef);

private:

	AActor* Tank = nullptr;  // It's possible ATank_C* reference


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


protected:

	//====== PlayerController don't connect ATank_C therefor we need not this function anymore =====///
	  /*UFUNCTION(BlueprintCallable, Category = "Setup")
	    ATank_C * GetControlledTank() const; // we need this function to call from Payer UI Widget*/
	
};
