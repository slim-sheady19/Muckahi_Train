// Fill out your copyright notice in the Description page of Project Settings.


#include "Train.h"
#include "TrackSpline.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATrain::ATrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

}

void ATrain::GetTrackSpline()
{
	//if TrackSpline was not set by hand in editor, get it automatically with GetActorOfClass
	if (!TrackSpline)
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

