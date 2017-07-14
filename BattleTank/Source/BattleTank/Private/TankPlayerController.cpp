// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"


ATank* ATankPlayerController:: GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector HitLocation;
	if(GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//find the crosshair position
	int32 ViewPortSizeX;
	int32 ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	
	FVector LookDirection;
	if(GetLookDirection(FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLocation), LookDirection))
	{
		if(GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			return true;
		}
	}

	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult Hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			Hit, 
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility))
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
