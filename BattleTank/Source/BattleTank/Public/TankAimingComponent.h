// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"


//Enum for aiming state
UENUM()
enum class EFiringState : uint8 
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};


class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitializeAiming(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	void AimAt(FVector OutHitLocation);

	EFiringState GetFiringState() const;
private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection = FVector(0, 0, 0);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();
	void MoveBarrelTowards();
	void MoveTurretTowards();
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 4000;
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;
protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
		EFiringState FiringState = EFiringState::Reloading;
	UPROPERTY(BlueprintReadOnly, Category = State)
		uint8 Ammo = 5;
	virtual void BeginPlay() override;


};
