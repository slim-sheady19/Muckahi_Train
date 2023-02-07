// Fill out your copyright notice in the Description page of Project Settings.


#include "Hoist.h"
#include "Kismet/KismetMathLibrary.h"

AHoist::AHoist()
{
	FrontConnectionDistanceFromRootBogey = 710.f;
	RearConnectionDistanceFromRootBogey = 50.f;
}

void AHoist::SetBogeyOnSpline(UPARAM(ref)USceneComponent* AttachPoint, UPARAM(ref)UStaticMeshComponent* Bogey)
{
	FVector attachPointCurrentLocation = AttachPoint->GetComponentLocation();
	FTransform transformClosestToSpline = TrackSpline->Spline->FindTransformClosestToWorldLocation(attachPointCurrentLocation, ESplineCoordinateSpace::World);

	Bogey->SetWorldTransform(transformClosestToSpline);
}

void AHoist::RotateSpreaderBar(UPARAM(ref)UStaticMeshComponent* SpreaderBarToRotate, UPARAM(ref)USceneComponent* AttachPointToLookAt)
{
	FVector spreaderBarLocation = SpreaderBarToRotate->GetComponentLocation();
	FVector attachPointLocation = AttachPointToLookAt->GetComponentLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(spreaderBarLocation, attachPointLocation);
	
	SpreaderBarToRotate->SetWorldRotation(lookAtRotation);
}

void AHoist::RotateAndScaleConnectorTube(
	UPARAM(ref)UStaticMeshComponent* ConnectorTube,
	UPARAM(ref)UStaticMeshComponent* StartConnector,
	UPARAM(ref)UStaticMeshComponent* TargetConnector)
{
	FVector startConnectorLocation = StartConnector->GetComponentLocation();
	FVector targetConnectorLocation = TargetConnector->GetComponentLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(startConnectorLocation, targetConnectorLocation);

	FVector vectorLength = startConnectorLocation - targetConnectorLocation;
	float length = vectorLength.Size();
	float lengthRatio = length / 100;

	ConnectorTube->SetWorldRotation(lookAtRotation);
	ConnectorTube->SetRelativeScale3D(FVector(lengthRatio, 1, 1));
}

//Update bogey position root bogey
//attach to spline rear bogey front
//update bogey position front bogey back
//attach front bogey front to spline
//rotate spreader bars (new function)
//rotate hoist
//rotate connector tube and set relative scale