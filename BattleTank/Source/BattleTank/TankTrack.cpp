// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%f throttle"), throttle);

	FVector ForceApplied = GetForwardVector() * throttle * MaxTrackDrivingForce;
	FVector TrackLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, TrackLocation);

}
