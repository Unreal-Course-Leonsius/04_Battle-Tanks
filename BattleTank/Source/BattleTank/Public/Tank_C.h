// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank_C.generated.h" // Put All includes above

class UTankBarrel_C;

UCLASS()
class BATTLETANK_API ATank_C : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank_C();

protected:

	UTankAimingComponent *TankAimingComponent = nullptr;


public:	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AimAt(FVector, FString);

	UFUNCTION(BlueprintCallable, Category = Setup)  // for use in Blueprint
	void SetBarrelReference(UTankBarrel_C *BarrelToSet); // use function in Tank_BP  // UTankBarrel is derived from UStaticMashComponent

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; // TODO find sensible default
	
};