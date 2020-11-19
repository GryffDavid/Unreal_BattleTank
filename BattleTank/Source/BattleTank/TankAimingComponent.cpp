// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) return false;

	return !AimDirection.Equals(Barrel->GetForwardVector(), 0.1);;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (AmmoLeft == 0)
		AimState = EAimingState::OutOfAmmo;
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime)
	{
		AimState = EAimingState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		AimState = EAimingState::Aiming;
	}
	else
	{
		AimState = EAimingState::Locked;
	}
	
	
}

void UTankAimingComponent::Initialise(UTankBarrel* barrel, UTankTurret* turret)
{
	Barrel = barrel;
	Turret = turret;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
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
		LaunchSpeed,
		false, 
		0, 
		0, 
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (haveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);	
	}
}

EAimingState UTankAimingComponent::GetAimState() const
{
	return AimState;
}

int UTankAimingComponent::GetAmmoLeft() const
{
	return AmmoLeft;
}

void UTankAimingComponent::Fire()
{
	if (AimState != EAimingState::Reloading && GetAmmoLeft() > 0)
	{
		if (!ensure(Barrel && ProjectileBlueprint)) return;
		//UE_LOG(LogTemp, Warning, TEXT("Fire!"));
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("ProjectileSocket"), Barrel->GetSocketRotation("Projectile Socket"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		AmmoLeft--;
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!ensure(Barrel && Turret)) return;

	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotation = aimDirection.Rotation();
	auto DeltaRotation = AimAsRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);

	if (FMath::Abs(DeltaRotation.Yaw) < 180)
		Turret->Rotate(DeltaRotation.Yaw);
	else
		Turret->Rotate(-DeltaRotation.Yaw);
}


