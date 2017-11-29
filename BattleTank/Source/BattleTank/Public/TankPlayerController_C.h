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

		ATank_C* GetControlledTank() const;

	   AActor* Tank = nullptr;  // It's possible ATank_C* reference
	    
	   void BeginPlay() override;
	
};
