// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank_C.h"
#include "AIController.h"
#include "TankAIController_C.generated.h"

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

	AActor* PlayerTank = nullptr;  // It's possible ATank_C* reference

	ATank_C* GetControlledTank() const;

	ATank_C* GetPlayerTank() const;

	
	
};
