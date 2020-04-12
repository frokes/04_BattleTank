// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "TankTurret.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Engine/StaticMesh.h"
#include "CollisionQueryParams.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// TODO Should this really tick?
}

void UTankAimingComponent::AimAt(FVector HitLocation, float ProjectileSpeed)
{
	if (!Barrel) { UE_LOG(LogTemp, Error, TEXT("No Barrel found!")) return; }
	if (!Turret) { UE_LOG(LogTemp, Error, TEXT("No Turret found!")) return; }

	FVector OutProjectileVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	// Calculate the projectile velocity
	TArray<AActor*> ActorsToIgnore;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutProjectileVelocity,
		StartLocation,
		HitLocation,
		ProjectileSpeed,
		false,
		50,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace,	// Parameter must be present to prevent bug (UE 4.24.2)
		FCollisionResponseParams::DefaultResponseParam,
		ActorsToIgnore,
		false
	);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutProjectileVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		// UE_LOG(LogTemp, Warning, TEXT("%s aiming barrel at at : %s "),*TankName , *AimDirection.ToString());
		MoveBarrel(AimDirection);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Aiming solution"));
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator : %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
