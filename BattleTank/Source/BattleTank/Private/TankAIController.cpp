// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ControlledTank = GetControlledTank();
	PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI did not find any player tank!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s found player tank : %s"), *ControlledTank->GetName(),*PlayerTank->GetName())
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank)
	{
		// TODO Move towards the player

		ControlledTank->AimAt(PlayerTank->GetActorLocation() + FVector(0.f, 0.f, 60.f));

		// Fire if ready
	}
	

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}