// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
/**
 * 
 */

class ATank;

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
	bool GetLookVectorHitLocation(FVector lookdirection, FVector& OUThitLocation) const;
	
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5, CrosshairYLocation = 1.0 / 3.0;

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000.0; //10km = 1,000,000 centimeters
};
