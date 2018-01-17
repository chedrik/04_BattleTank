// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

//depends on mvmt component due to pathfind

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto AITank = GetPawn();
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!ensure(AITank && PlayerTank)) { return; }
	if (ensure(PlayerTank))
	{
		//move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);//TODO check radius in CM
		//aim at player
		auto AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		// fire if ready
		if (AimingComponent->GetFiringState() == EFiringState::Locked) {
			AimingComponent->Fire();
		}
	}
}
