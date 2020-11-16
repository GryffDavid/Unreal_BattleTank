// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	auto Time = GetWorld()->GetTimeSeconds();
	auto ElevationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto ClampPitch = FMath::Clamp(rawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(ClampPitch, 0, 0));
}
