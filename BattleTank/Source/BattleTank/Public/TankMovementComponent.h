// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Action)
	void IntentMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	void IntentTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = Action)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	// Check best protection, is public nescessary?
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

};
