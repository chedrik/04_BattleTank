// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts or when spawned
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::ApplySidewaysForce()
{
	auto SlipSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAccel = -(SlipSpeed / DeltaTime)*GetRightVector(); // apply accel in opposite direction of current slip
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = TankRoot->GetMass()*CorrectionAccel / 2; // two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}
void UTankTrack::SetThrottle(float Throttle)
{
	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
	CurrentThrottle = CurrentThrottle + Throttle;

}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector()*CurrentThrottle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //goes to the top level tank which the track belongs to
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


