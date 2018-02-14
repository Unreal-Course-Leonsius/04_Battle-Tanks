// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankTrack_C.h"
#include "TankMovementComponent.h"


UTankMovementComponent::UTankMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("hokydoky TankMovementComponent Constructor C++ ..."))
		// ...
}


void UTankMovementComponent::Initialize(UTankTrack_C *LeftTrackToSet, UTankTrack_C *RightTrackToSet)
{
	if (!ensure(LeftTrackToSet) || !ensure(RightTrackToSet)) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{


	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	RightTrack->SetThrottle(-Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{

	// We need not { SUper::equestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) } because we only need MoveVelocity
	
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AiForwardIntention = MoveVelocity.GetSafeNormal();


	auto ForwardThrow = FVector::DotProduct(TankForward, AiForwardIntention); // DotProduct() implementation { return A | B } its not binary operation its overloaded operator
	IntendMoveForward(ForwardThrow);
	

	
	auto RightThrow = FVector::CrossProduct(TankForward, AiForwardIntention);
	IntendTurnRight(RightThrow.Z);
	

	float TurnValue = (TankForward.X * AiForwardIntention.Y) - (TankForward.Y * AiForwardIntention.X);
	

	/*UE_LOG(LogTemp, Warning, TEXT("TankForward %s"), *TankForward.ToString());
	UE_LOG(LogTemp, Warning, TEXT("AiForwardIntention  %s"), *AiForwardIntention.ToString());
	UE_LOG(LogTemp, Warning, TEXT("RightThrow  %s"), *RightThrow.ToString()); */
}
