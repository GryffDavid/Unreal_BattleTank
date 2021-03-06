// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed)
{
	relativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	auto RotationChange = relativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawNewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0, rawNewRotation, 0));
}
