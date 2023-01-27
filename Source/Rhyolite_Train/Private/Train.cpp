// Fill out your copyright notice in the Description page of Project Settings.


#include "Train.h"
#include "TrackSpline.h"
#include "TrainController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATrain::ATrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBogey = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Bogey"));
	SetRootComponent(RootBogey);
	RootBogey->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ATrain::BeginPlay()
{
	Super::BeginPlay();

	GetTrackSpline();
}

// Called every frame
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

void ATrain::SetOnTrack()
{
	GetTrackSpline();

	if (TrackSpline)
	{
		FTransform splineTransformFromPosition = TrackSpline->Spline->GetTransformAtDistanceAlongSpline(StartPosition, ESplineCoordinateSpace::World);
		RootBogey->SetWorldTransform(splineTransformFromPosition);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No track spline in level!"));
	}

}

void ATrain::Destroyed()
{
	TrainController->CleanTrainArray(this);

	Super::Destroyed();
}

