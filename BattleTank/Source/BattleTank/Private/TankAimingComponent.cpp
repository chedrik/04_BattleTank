// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"


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

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calc OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchVelocity,
			StartLocation,
			OutHitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace) //bug if not included
			) 
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);

	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// calc difference between current position and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); //takes x direction along barrel and turns into roll,pitch,yaw struct
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	// calc difference between current position and aim direction

	auto TurretRotator = Turret->GetForwardVector().Rotation(); //takes x direction along turret and turns into roll,pitch,yaw struct
	auto AimAsTurretRotator = AimDirection.Rotation();
	auto DeltaTurretRotator = AimAsTurretRotator - TurretRotator;

	if (FMath::Abs(DeltaTurretRotator.Yaw) > 180)
	{
		Turret->Rotate(DeltaTurretRotator.Yaw * -1);
	}
	else
	{
		Turret->Rotate(DeltaTurretRotator.Yaw);
	}

}