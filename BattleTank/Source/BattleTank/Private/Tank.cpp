// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = 0.f;
	if (DamageAmount >= CurrentHealth) {
		DamageToApply = CurrentHealth;
		CurrentHealth = 0.f;	
		OnDeath.Broadcast();
	}
	else {
		CurrentHealth -= DamageAmount;
		DamageToApply = DamageAmount;
	}
	//UE_LOG(LogTemp, Warning, TEXT("current health: %f"), CurrentHealth);
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}