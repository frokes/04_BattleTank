// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "CollisionQueryParams.h"
#include "Camera/PlayerCameraManager.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller BeginPlay()"))

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not controlling any tank!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Now controlling : %s"), *(ControlledTank->GetName()))
	}
	

}

void ATankPlayerController::Tick( float DeltaTime)
{
	Super::Tick( DeltaTime );

	AimTowardsCrosshair();

	// UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking!"))
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter

	if(GetSightRayHitLocation(HitLocation))
	{
	// UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString())
		GetControlledTank()->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landsc
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;

	// De-project the screen position of the crosshair to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line trace along that look direction and see what we hit (up to max range)
	
		GetLookVectorHitLocation(LookDirection, HitLocation);
		
		// UE_LOG(LogTemp, Warning, TEXT("Line trace aimed at : %s"), *HitLocation.ToString())
	}
	


	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0.f, 0.f, 0.f);
	return false;
}
