// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float AzimuthChange = RelativeSpeed * DegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Azimuth = RelativeRotation.Yaw + AzimuthChange;
	UE_LOG(LogTemp, Warning, TEXT("Rotating to : %f"), Azimuth)

	SetRelativeRotation(FRotator(0, Azimuth, 0));
}