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
	
	
	ATank_C* GetControlledTank() const;

	AActor* Tank = nullptr;  // It's possible ATank_C* reference

	void BeginPlay() override;
	
};
