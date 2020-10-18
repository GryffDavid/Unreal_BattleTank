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
	UE_LOG(LogTemp, Warning, TEXT("Tick"));
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) return;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

