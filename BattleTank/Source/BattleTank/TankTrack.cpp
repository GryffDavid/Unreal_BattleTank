// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	UE_LOG(LogTemp, Warning, TEXT("TRACK TICK"));
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Divide by two because there are two tracks

	TankRoot->AddForce(CorrectionAcceleration);
}

void UTankTrack::SetThrottle(float throttle)
{
	FVector ForceApplied = GetForwardVector() * throttle * MaxTrackDrivingForce;
	FVector TrackLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, TrackLocation);

}
