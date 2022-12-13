// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackSpline.h"
#include "Engine\Classes\Components\InstancedStaticMeshComponent.h"


// Sets default values
ATrackSpline::ATrackSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);

	InstancedTrack = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Track"));
	InstancedChain = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Chain"));
	InstancedHangar = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Hangar"));

	//Set meshes with hard references with hard reference
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		trackMesh(TEXT("'/Game/Meshes/Rail/track_section_track/track_section_track.track_section_track'"));
	TrackMesh = trackMesh.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		chainMesh(TEXT("'/Game/Meshes/Rail/track_section_chainlink/track_section_chainlink.track_section_chainlink'"));
	TrackMesh = chainMesh.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		hangarMesh(TEXT("'/Game/Meshes/Rail/track_section_hangar/track_section_hangar.track_section_hangar'"));
	TrackMesh = hangarMesh.Object;

	InstancedTrack->SetStaticMesh(TrackMesh);
	InstancedChain->SetStaticMesh(ChainMesh);
	InstancedHangar->SetStaticMesh(HangarMesh);

	//Set Spacing and NumInstances
	FBox TrackBoundingBox = TrackMesh->GetBoundingBox();
	FVector BoxLength = (TrackBoundingBox.Max - TrackBoundingBox.Min);
	Spacing = BoxLength.X + Offset;
	NumInstances = FMath::Floor(Spline->GetSplineLength() / Spacing);

	//Generate Instances
	for (int i = 0; i <= NumInstances; i++)
	{
		GetLocationAtIndex(i);
	}
}

FVector ATrackSpline::GetLocationAtIndex(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("yo"));
	FVector vector = FVector(10, 10, 10);
	return vector;
}

// Called when the game starts or when spawned
void ATrackSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrackSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

