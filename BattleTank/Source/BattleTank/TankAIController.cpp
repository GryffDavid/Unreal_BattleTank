// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


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

		MoveToActor(PlayerTank, 3000);
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		//ControlledTank->Fire();
	}	

	//AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Tick"));
}