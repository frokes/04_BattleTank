// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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

	// AimTowardsCrosshair();

	UE_LOG(LogTemp, Warning, TEXT("Player Controller ticking!"))
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank){ return };

	// Get world location through crosshair (by linetrace)

	// If the linetrace hits something 
		// Tell the controlled tank to aim at this point
}