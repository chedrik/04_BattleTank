// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller has no aiming component at begin play"));
		return;
	}

	auto ControlledTank = GetPawn();
	if (!ensure(ControlledTank)) {
		UE_LOG(LogTemp, Warning, TEXT("Not Possesing A Tank"));
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Possesing Tank %s"),*(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("TEST TICK"));
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!(GetPawn())) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if(!ensure(AimingComponent)) { return; }
	
	FVector HitLocation; //Out parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
		//tell controlled tank to aim there
	}
}

//get world location by linetracing through crosshair
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector& OutHitLocation) const
{
	//Find crosshair position in pixels
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); 
	FVector2D ScreenLocation = FVector2D(CrossHairXLocation * ViewportSizeX, CrossHairYLocation * ViewportSizeY);

	// Deproject screen position of crosshair to world coordinates
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// line trace along that direction, see what is hit
		return GetLookVectorHitLocation(OutHitLocation,LookDirection);
	}
	
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; // discard
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
		return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//subscribe to tank death
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}


