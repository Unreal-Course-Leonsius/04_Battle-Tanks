// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController_C.generated.h"

// Forward Declaration
class UTankAimingComponent;
//class ATank_C;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController_C : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	
	// How close can AI Tank get in cm
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 10000;

private:

	AActor* PlayerTankK = nullptr;  // It's not possible ATank_C* reference because it is AActor not Atank_C


	// Local Varieable for not fireing from the start
	float StartProjectile = 10;

private:

	//============ we need not thus two functions because TankAIController don't connect to ATank_C anymore ======///
	  //ATank_C* GetControlledTank() const;

	  //ATank_C* GetPlayerTank() const;
	
};
