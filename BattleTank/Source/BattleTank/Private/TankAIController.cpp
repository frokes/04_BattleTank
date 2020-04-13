// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ControlledTank = Cast<ATank>(GetPawn());
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	
	if (PlayerTank)
	{
		// UE_LOG(LogTemp, Warning, TEXT("I am an AI!"));
		// TODO Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm

		ControlledTank->AimAt(PlayerTank->GetActorLocation() + FVector(0.f, 0.f, 60.f));

		//ControlledTank->Fire();
	}
}
