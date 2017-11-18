// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

	void BeginPlay() override;
	

private:
	ATank* GetControlledTank() const;

	void AimTowardsCrosshair(); //mode tank barrel so shot hits where crosshair hits world	

	bool GetSightRayHitLocation(OUT FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector & HitLocation, FVector LookDirection) const;

	UPROPERTY(EditAnywhere)
	float  CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float  CrossHairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

};
