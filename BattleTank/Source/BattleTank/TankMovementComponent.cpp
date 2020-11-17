// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Rotate)
{
	if (!LeftTrack || !RightTrack) return;

	LeftTrack->SetThrottle(Rotate);
	RightTrack->SetThrottle(-Rotate);
}

void UTankMovementComponent::Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//Don't call super. Replacing functionality.

	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto vectorToPlayer = MoveVelocity.GetSafeNormal();

	float throttleValue = FVector::DotProduct(tankForward, vectorToPlayer);
	auto rightThrow = FVector::CrossProduct(tankForward, vectorToPlayer).Z;

	IntendRotateClockwise(rightThrow);
	IntendMoveForward(throttleValue);
}