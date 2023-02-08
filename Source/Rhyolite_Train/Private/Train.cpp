/**

Train parent class that sets default values and contains functions common to all children.

Original author: Shea Galley
Current maintainer: Shea Galley

*********************************************************************************/


#include "Train.h"
#include "TrackSpline.h"
#include "TrainController.h"
#include "Kismet/GameplayStatics.h"


ATrain::ATrain()
{
	PrimaryActorTick.bCanEverTick = true;

	RootBogey = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Bogey"));
	SetRootComponent(RootBogey);
	RootBogey->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

/**
Call GetTrackSpline at Beginplay in case a train's TrackSpline is null
*********************************************************************************/
void ATrain::BeginPlay()
{
	Super::BeginPlay();

	GetTrackSpline();
}


void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//do nothing in tick if we do not want train moving
	if (Disabled)
	{
		return;
	}

	UpdateDistance(DeltaTime);
}

/**
Called from child BP in tick
*********************************************************************************/
void ATrain::UpdateBogeyPosition(UStaticMeshComponent* Bogey, const float DeltaBogeyDistanceFromRootBogey)
{
	if (Bogey == nullptr)
	{
		return;
	}

	float currentDistance = Distance + StartPosition + DeltaBogeyDistanceFromRootBogey;
	FTransform splinePositionTransform = TrackSpline->Spline->GetTransformAtDistanceAlongSpline(currentDistance, ESplineCoordinateSpace::World);

	Bogey->SetWorldTransform(splinePositionTransform);
}

/**
Updating distance float in Tick
*********************************************************************************/
void ATrain::UpdateDistance(float DeltaTime)
{
	float deltaDistance = Speed * DeltaTime;
	float distanceTravelled = Distance + deltaDistance;

	Distance = distanceTravelled;
}

void ATrain::GetTrackSpline()
{
	//if TrackSpline was not set by hand in editor, get it automatically with GetActorOfClass
	if (TrackSpline == nullptr)
	{
		AActor* foundTrack = UGameplayStatics::GetActorOfClass(GetWorld(), ATrackSpline::StaticClass());

		//if there is a track in the level then assign it to TrackSpline
		if (foundTrack)
		{
			TrackSpline = Cast<ATrackSpline>(foundTrack);
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No track in level"));
		}
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Track is valid"));
	}
}

/**
Called from TrainController when it has spawned a train
*********************************************************************************/
void ATrain::SetOnTrack(float DistanceFromNextTrain = 0.f)
{
	GetTrackSpline();

	if (TrackSpline)
	{
		FTransform splineTransformFromPosition = TrackSpline->Spline->GetTransformAtDistanceAlongSpline(DistanceFromNextTrain, ESplineCoordinateSpace::World);
		RootBogey->SetWorldTransform(splineTransformFromPosition);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No track spline in level!"));
	}

}


/**
Same function as above but takes no float so we can call it manually from editor
*********************************************************************************/
void ATrain::SetOnTrackEditor()
{
	GetTrackSpline();

	if (TrackSpline)
	{
		float positionOnSpline = StartPosition;
		FTransform splineTransformFromPosition = TrackSpline->Spline->GetTransformAtDistanceAlongSpline(positionOnSpline, ESplineCoordinateSpace::World);
		RootBogey->SetWorldTransform(splineTransformFromPosition);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No track spline in level!"));
	}
}

/**
Overriding Destroyed() to remove deleted train in editor from TrainsInLevel array
*********************************************************************************/
void ATrain::Destroyed()
{
	Super::Destroyed();

	if (IsValid(TrainController))
	{
		TrainController->RemoveTrainFromArray(this);
	}
	
}

