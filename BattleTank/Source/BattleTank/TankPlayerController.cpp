// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is posessing: %s"), *(controlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(0.0f, 0.0f, 0.0f);

	int32 viewPortSizeX, viewPortSizeY;

	GetViewportSize(viewPortSizeX, viewPortSizeY);
	auto ScreenLocation = FVector2D(viewPortSizeX * CrosshairXLocation, viewPortSizeY * CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector& OUTlookDirection) const
{
	FVector WorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, WorldLocation, OUTlookDirection);	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookdirection, FVector& OUThitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (lookdirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) 
	{
		OUThitLocation = HitResult.Location;
		return true;
	}

	OUThitLocation = FVector(0);
	return false;
}

