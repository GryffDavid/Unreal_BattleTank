// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

void ATank::BeginPlay()
{	
	Super::BeginPlay();
}

// Sets default values
ATank::ATank()
{	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damgeTaken = FMath::Clamp<float>(Damage, 0, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("TOOK DAMAGE %f"), damgeTaken);

	CurrentHealth -= damgeTaken;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK DEAD"));
	}

	return damgeTaken;
}

