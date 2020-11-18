// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingState : uint8
{
	Aiming,
	Locked,
	Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EAimingState AimState = EAimingState::Locked;

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* barrel, UTankTurret* turret);	

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UPROPERTY(BlueprintReadWrite, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	void AimAt(FVector hitLocation);
	
private:
	UTankAimingComponent();

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.0f;

	


	double LastFireTime = 0.0;
	
	void MoveBarrelTowards(FVector aimDirection);
};
