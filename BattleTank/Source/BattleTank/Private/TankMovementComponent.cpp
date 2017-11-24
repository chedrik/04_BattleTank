// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "BattleTank.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO prevent double addition from 2 control inputs
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO prevent double addition from 2 control inputs
}

void UTankMovementComponent::Initialize(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet)
{
	if (!LTrackToSet || !RTrackToSet) { return; }
	LeftTrack = LTrackToSet;
	RightTrack = RTrackToSet;

}