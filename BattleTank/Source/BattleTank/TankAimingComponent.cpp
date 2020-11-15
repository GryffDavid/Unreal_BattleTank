// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{	
	//UE_LOG(LogTemp, Warning, TEXT("Firing at %f"), launchSpeed);

	//auto OurTankName = GetOwner()->GetName();
	//auto BarrelLocation = Barrel->GetComponentLocation();
	//UE_LOG(LogTemp, Warning, TEXT("%s AIMING AT %s FROM %s"), *OurTankName, *hitLocation.ToString(), *BarrelLocation.ToString());

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileSocket"));
	
	if (UGameplayStatics::SuggestProjectileVelocity( this, OUT OutLaunchVelocity, StartLocation, hitLocation, launchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = aimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;

	Barrel->Elevate(12);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * barrelToSet)
{
	Barrel = barrelToSet;
}

