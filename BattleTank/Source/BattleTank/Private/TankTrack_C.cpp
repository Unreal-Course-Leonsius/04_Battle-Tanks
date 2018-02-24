// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack_C.h"


UTankTrack_C::UTankTrack_C()
{
	PrimaryComponentTick.bCanEverTick = false; // we need not Ticking. OnHit() is ticking
	
}

void UTankTrack_C::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack_C::OnHit);
}

void UTankTrack_C::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Drive the Tracks
	DriveTrack();
	// Apply Sideways Force
	ApplySidewaysForce();
	CurrentThrottle = 0; // because in bottom we have CurrentThrottle + Throttle
}


void UTankTrack_C::ApplySidewaysForce()
{
	// Calculate sideways slippage speed
	auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	/*UE_LOG(LogTemp, Warning, TEXT("RightVector %s"), *GetRightVector().ToString());
	UE_LOG(LogTemp, Error, TEXT("ComponentVelocity %s"), *GetComponentVelocity().ToString());
	UE_LOG(LogTemp, Warning, TEXT("ForwardVector %s"), *GetOwner()->GetActorForwardVector().ToString());*/

	// Work-out required acceleration and directoin this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto Acceleration = -((SlippageSpeed / DeltaTime) * GetRightVector());

	// Calculate and apply sideways for ( F = ma )
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto ForceSideway = TankRoot->GetMass() * Acceleration / 2; // dived 2 because we have two tracks
	TankRoot->AddForce(ForceSideway);

	/*auto TankName = GetOwner()->GetName();
	if (TankName == "Tank_BP_C_0")
	{
	UE_LOG(LogTemp, Warning, TEXT("UTankTrack Tikcing...%f"), SlippageSpeed);
	}*/

}

void UTankTrack_C::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack_C::DriveTrack()
{
	// TODO clamp actual Throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForce(ForceApplied);
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);


	/*
	auto ForwardV = GetForwardVector();
	auto Loction = GetComponentLocation();
	auto ForwardVMult = GetForwardVector() * Throttle * TankMaxDrivingForce;
	auto DirectionX = GetComponentRotation();
	UE_LOG(LogTemp, Warning, TEXT("ForwardV = %s, ForceApplied = %s, ComponentLoction = %s || Throttle = %f"),*ForwardV.ToString(),*ForceApplied.ToString(), *Loction.ToString(),Throttle);
	*/
}



//========================= Function We need not ======================///

/*void UTankTrack_C::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

}*/
