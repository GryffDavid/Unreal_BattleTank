// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto playerTank = GetPlayerTank();

	if (!playerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI cannot find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI found player tank: %s"), *(playerTank->GetName()));

	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);

}