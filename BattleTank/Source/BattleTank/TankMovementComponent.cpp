// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack)
{
	if (!leftTrack || !rightTrack) return;

	LeftTrack = leftTrack;
	RightTrack = rightTrack;
}
