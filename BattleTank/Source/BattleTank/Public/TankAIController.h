// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */


UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;//called when possessed
protected:
	//how close AI tank can get to player
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AcceptanceRadius = 3000;
	UFUNCTION()
		void OnPossessedTankDeath();
};
