// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
private:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	void Tick(float deltaSeconds);
	ATank* GetPlayerTank() const;
	//how close can ai tank get to player
	float AcceptanceRadius = 3000;
	
};
