// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack_C;

/**
 * Responsible for driving the Tank's Track
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack_C *LeftTrackToSet, UTankTrack_C *RightTrackToSet);


	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnLeft(float Throw); // It has not Ben's code

	
private:

	UTankMovementComponent();

	// Called from the Pathfindng logic by the AIController, MoveToActor(); 
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack_C *LeftTrack = nullptr;
	UTankTrack_C *RightTrack = nullptr;
};