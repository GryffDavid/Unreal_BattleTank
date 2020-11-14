// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"	
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	ATank* GetControlledTank() const;
	
	void BeginPlay() override;
	void Tick(float deltaSeoonds) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D screenLocation, FVector& OUTlookDirection) const;
	
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5, CrosshairYLocation = 1.0 / 3.0;
};
