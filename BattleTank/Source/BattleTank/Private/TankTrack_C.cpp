// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack_C.h"



void UTankTrack_C::SetThrottle(float Throttle)
{
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s = %f"), *Name, Throttle);

	// TODO clamp actual Throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForce(ForceApplied);
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);


   /*
	auto ForwardV = GetForwardVector();
	auto Loction = GetComponentLocation();
	auto ForwardVMult = GetForwardVector() * Throttle * TankMaxDrivingForce;
	auto DirectionX = GetComponentRotation();
	UE_LOG(LogTemp, Warning, TEXT("ForwardV = %s, ForceApplied = %s, ComponentLoction = %s || Throttle = %f"),*ForwardV.ToString(),*ForceApplied.ToString(), *Loction.ToString(),Throttle);
	*/
}
