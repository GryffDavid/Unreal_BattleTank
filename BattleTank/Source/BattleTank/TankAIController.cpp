// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//Move towards player
		//Aim at player
		//Shoot at player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//ControlledTank->Fire();
	}	

	//AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
}