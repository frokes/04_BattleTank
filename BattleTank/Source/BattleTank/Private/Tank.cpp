// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Components/SceneComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	UE_LOG(LogTemp, Warning, TEXT("OWL : %s Constructor called!"), *GetName())
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("OWL : %s BeginPlay() called!"), *GetName())
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, ProjectileSpeed);
}

void ATank::Fire()
{
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{ 
		FName Socket = FName("Projectile");
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(*ProjectileBlueprint, Barrel->GetSocketLocation(Socket), Barrel->GetSocketRotation(Socket));
		Projectile->FireProjectile(ProjectileSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

	else
	{
		return;
	}
}
