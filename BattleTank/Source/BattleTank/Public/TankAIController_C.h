// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController_C.generated.h"

// Forward Declaration
class ATank_C;

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

private:

	AActor* PlayerTank = nullptr;  // It's not possible ATank_C* reference because it is AActor not Atank_C

	ATank_C* GetControlledTank() const;

	ATank_C* GetPlayerTank() const;

	
	
};
