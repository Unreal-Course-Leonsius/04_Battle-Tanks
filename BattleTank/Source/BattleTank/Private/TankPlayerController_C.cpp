// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController_C.h"

ATank_C * ATankPlayerController_C::GetControlledTank() const
{
	return Cast<ATank_C>(GetPawn());
}
