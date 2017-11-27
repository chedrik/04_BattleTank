// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	Throw = FMath::Clamp<float>(Throw, -1, 1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	Throw = FMath::Clamp<float>(Throw, -1, 1);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO investigate different friction / force for turning
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto Dotted = FVector::DotProduct(TankForwardVector, AIForwardIntention);
	auto Crossed = FVector::CrossProduct(TankForwardVector, AIForwardIntention);
	IntendTurnRight(Crossed.Z);
	IntendMoveForward(Dotted);
	

}


void UTankMovementComponent::Initialize(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet)
{
	if (!ensure(LTrackToSet && RTrackToSet)) { return; }
	LeftTrack = LTrackToSet;
	RightTrack = RTrackToSet;

}


