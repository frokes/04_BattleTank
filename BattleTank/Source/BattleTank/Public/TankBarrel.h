// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	

public:
	// -1 max downwards, +1 max uppwards elevation speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 25;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDepression = -2;
};
