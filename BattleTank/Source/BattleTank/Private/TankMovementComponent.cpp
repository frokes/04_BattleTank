// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Math/Vector.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntentMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO Prevent additive controls leading to additive speed
}

void UTankMovementComponent::IntentTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO Prevent additive controls leading to additive speed
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super as we are replacing the function
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto TankUp = GetOwner()->GetActorUpVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntentMoveForward(ForwardThrow);
	IntentTurnRight(RightThrow.Z);
}