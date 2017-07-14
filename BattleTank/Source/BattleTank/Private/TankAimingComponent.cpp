// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}


void UTankAimingComponent::MoveBarrelTowardsTarget(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{

	if (!Barrel || !Turret) { return; }
	auto TankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	UE_LOG(LogTemp, Warning, TEXT("tank aims at something"));
	if(UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		WorldSpaceAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowardsTarget(AimDirection);
	}


}

