// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankAimingComponent.h"
//#include "Tank_C.h"
#include "TankPlayerController_C.h"


void ATankPlayerController_C::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	FVector2D ScreenSize;
	GetWorld()->GetGameViewport()->GetViewportSize(ScreenSize);
	UE_LOG(LogTemp, Error, TEXT("Screen size = %s"), *ScreenSize.ToString());*/
	if (!ensure(GetPawn())) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	FindAimingComponent(AimingComponent);
}



void ATankPlayerController_C::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("It's TankPlayrController Ticking..."));
}



void ATankPlayerController_C::AimTowardCrosshair()
{
	if (!ensure(GetPawn())) { return; }

	FVector OutHitLocation; // OUT Parameter
	FString HitObjectName;  // OUT Parameter
	bool bGotHitLocation = GetSightRayHitLocation(OutHitLocation, HitObjectName);
	UE_LOG(LogTemp, Warning, TEXT("bGotHitLocation %i"), bGotHitLocation); // boolien Log i = bool = integer;

	if (bGotHitLocation) // Has "sied-effect", is going to Line trace
	{
		// Tell controlled tank to aim at this point
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt(OutHitLocation,HitObjectName);
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
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation, HitObN);
	}

	
	return false;
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


/*ATank_C * ATankPlayerController_C::GetControlledTank() const
{
     //============== WE USE GetPawn() INSTED OF Cast<ATank_C>(GetPawn()) =============//
         // Because we want to connect AimingComponent directly and
         //TankPlayerController's Pawn can find ActorComponent in the class which is derived from it because
         // FindComponentByClass is a function on AActor, it loops through it’s components and
         //returns the first UActorComponent* of the specified type which must be derived from UActorComponent
    return Cast<ATank_C>(GetPawn());
}*/