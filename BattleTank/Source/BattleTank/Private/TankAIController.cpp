// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto AITank = GetAITank();
	auto PlayerTank = GetPlayerTank();
	if (!AITank) {
		UE_LOG(LogTemp, Warning, TEXT("No AI  Tank"));
	}
	else if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("No Player Tank Found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank %s sees player %s"), *(AITank->GetName()),*(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}