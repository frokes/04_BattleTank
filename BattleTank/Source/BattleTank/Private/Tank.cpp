// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
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

	// No need to protect aiming pointer as its added on construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{;
	TankAimingComponent->SetTurretReference(TurretToSet);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
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
