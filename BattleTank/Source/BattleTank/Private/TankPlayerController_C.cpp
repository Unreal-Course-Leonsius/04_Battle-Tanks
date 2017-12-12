// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController_C.h"


void ATankPlayerController_C::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	FVector2D ScreenSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ScreenSize);
	UE_LOG(LogTemp, Error, TEXT("Screen size = %s"), *ScreenSize.ToString());*/

    Tank = GetControlledTank();
	FString TankName = Tank->GetName();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Possesses Tank's:  %s"),*TankName);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not Possessess anything")); 
}



void ATankPlayerController_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("It's TankPlayrController Ticking..."));
}



ATank_C * ATankPlayerController_C::GetControlledTank() const
{
	return Cast<ATank_C>(GetPawn());
}



void ATankPlayerController_C::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; // OUT Parameter
	FString HitObjectName;  // OUT Parameter
	if (GetSightRayHitLocation(OutHitLocation,HitObjectName)) // Has "sied-effect", is going to Line trace
	{
		// TODO Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(OutHitLocation,HitObjectName);
	}

}

// Get World location if linetrace through corsshair, true if hits Landscape
bool ATankPlayerController_C::GetSightRayHitLocation(FVector & OutHitLocation, FString & HitObN) const
{

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;           // FVector2D ViewportSize;
	GetViewportSize(ViewportSizeX, ViewportSizeY); // GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize); mivigebdit pirdapir Screen size shegvedzlo X da Y coordinati calke amogveyvana { ViewportSize.X; ViewportSize.Y }

	FVector2D ScreenLocation(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);


	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *LookDirection.ToString());
		// Line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, OutHitLocation, HitObN);
	}

	
	return true;
}

bool ATankPlayerController_C::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation, FString & HitObN) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	/*DrawDebugLine(
		GetWorld(),
		StartLocation,
		EndLocation,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		5.f
	);*/

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		HitObN = HitResult.GetActor()->GetName();
		return true;
	}
	OutHitLocation = FVector(0);
	HitObN = "None";
	return false;
}

bool ATankPlayerController_C::GetLookDirection(FVector2D & ScreenLocation, FVector & LookDirection) const
{
	FVector Camera(1.0); // will be discard
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		Camera,
		LookDirection
	);

}
