// Fill out your copyright notice in the Description page of Project Settings.


#include "Hoist.h"

void AHoist::SetBogeyOnSpline(UPARAM(ref)USceneComponent* AttachPoint, UPARAM(ref)UStaticMeshComponent* Bogey)
{
	FVector attachPointCurrentLocation = AttachPoint->GetComponentLocation();
	FTransform transformClosestToSpline = TrackSpline->Spline->FindTransformClosestToWorldLocation(attachPointCurrentLocation, ESplineCoordinateSpace::World);

	Bogey->SetWorldTransform(transformClosestToSpline);
}

//Update bogey position root bogey
//attach to spline rear bogey front
//update bogey position front bogey back
//attach front bogey front to spline
//rotate spreader bars (new function)
//rotate hoist
//rotate connector tube and set relative scale