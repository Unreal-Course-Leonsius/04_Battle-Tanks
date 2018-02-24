// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack_C.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to the Tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack_C : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set the Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	UPROPERTY(EditDefaultsOnly)
	float TankMaxDrivingForce = 40000000.0;
	

private:
	UTankTrack_C();

	// ========= We need not TickComponent() because we hava OnHit and it Ticks
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override; 

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	float CurrentThrottle = 0;
	void DriveTrack();

	// this Ticks in every frame when the Tank is on something (which has Block Collision) 
	UFUNCTION()
	void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
