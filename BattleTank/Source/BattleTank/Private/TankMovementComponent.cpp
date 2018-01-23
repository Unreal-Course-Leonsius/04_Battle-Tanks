// Copyright EmbraceIT Ltd.

#include "BattleTank.h"
#include "TankTrack_C.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialize(UTankTrack_C *LeftTrackToSet, UTankTrack_C *RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	//UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward throw: %f"), Throw);

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
	//UE_LOG(LogTemp, Warning, TEXT("ForwadThrow %f"), ForwardThrow);

	
	auto RightThrow = FVector::CrossProduct(TankForward, AiForwardIntention);
	IntendTurnRight(RightThrow.Z);
	//UE_LOG(LogTemp, Warning, TEXT("ForwadThrow %s"), *RightThrow.ToString());

	float TurnValue = (TankForward.X * AiForwardIntention.Y) - (TankForward.Y * AiForwardIntention.X);
	//UE_LOG(LogTemp, Warning, TEXT("TurnValue %f"), TurnValue);
	

	/*UE_LOG(LogTemp, Warning, TEXT("TankForward %s"), *TankForward.ToString());
	UE_LOG(LogTemp, Warning, TEXT("AiForwardIntention  %s"), *AiForwardIntention.ToString());
	UE_LOG(LogTemp, Warning, TEXT("RightThrow  %s"), *RightThrow.ToString()); */
}
