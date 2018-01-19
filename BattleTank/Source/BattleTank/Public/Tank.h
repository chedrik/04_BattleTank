// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "TankAimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


public:
	//percentage of starting health 0->1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	FTankDelegate OnDeath;
private:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const & DamageEvent,
		class AController * EventInstigator,
		AActor * DamageCauser
	) override;

	UPROPERTY(EditDefaultsOnly)
		float StartingHealth = 50.f;

	float CurrentHealth;
	
};
