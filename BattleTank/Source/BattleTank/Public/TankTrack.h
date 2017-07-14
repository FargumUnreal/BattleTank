// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category=Input)
	void SetThrottle(float Throttle);

	//max force in newtons per track
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // tank mass * acceleration at 1g (10 m/sec)
	
	
};
