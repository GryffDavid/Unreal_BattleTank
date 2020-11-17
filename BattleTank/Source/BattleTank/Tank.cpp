// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

void ATank::BeginPlay()
{	
	Super::BeginPlay();
}

void ATank::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire!"));

	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;

	if (ensure(Barrel && isReloaded))
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("ProjectileSocket"), Barrel->GetSocketRotation("Projectile Socket"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

// Sets default values
ATank::ATank()
{	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector hitLocation)
{
	if (!ensure(TankAimingComponent)) return;
	TankAimingComponent->AimAt(hitLocation, LaunchSpeed);	
}

