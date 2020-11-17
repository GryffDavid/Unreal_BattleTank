// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* barrel, UTankTurret* turret)
{
	Barrel = barrel;
	Turret = turret;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!ensure(Barrel)) return;
	if (!ensure(Turret)) return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));
	
	bool haveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OUT OutLaunchVelocity,
		StartLocation,
		hitLocation,
		launchSpeed,
		false, 
		0, 
		0, 
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (haveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);	
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!ensure(Barrel || !Turret)) return;

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = aimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);
	Turret->Rotate(DeltaRotation.Yaw);
}


