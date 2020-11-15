// Fill out your copyright notice in the Description page of Project Settings.


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
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{		
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation:%s"), *HitLocation.ToString());
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
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation:%s"), *ScreenLocation.ToString());

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	//UE_LOG(LogTemp, Warning, TEXT("worldDirection:%s"), *LookDirection.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("OutHitLocation:%s"), *OutHitLocation.ToString());
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

	return false;
}

