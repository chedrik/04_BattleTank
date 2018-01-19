// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "ParticleHelper.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere)
		URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditDefaultsOnly)
		float DestroyDelay = 7.f;
	UPROPERTY(EditDefaultsOnly)
		float DamageAmount = 5.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);
private:
	void OnTimerExpire();

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	UProjectileMovementComponent* ProjectileMovement = nullptr;




};
