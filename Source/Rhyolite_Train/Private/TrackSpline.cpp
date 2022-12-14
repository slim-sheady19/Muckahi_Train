// Fill out your copyright notice in the Description page of Project Settings.


#include "TrackSpline.h"
#include "Engine\Classes\Components\InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"


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

	//Set meshes with hard references
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		trackMesh(TEXT("'/Game/Meshes/Rail/track_section_track/track_section_track.track_section_track'"));
	TrackMesh = trackMesh.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		chainMesh(TEXT("'/Game/Meshes/Rail/track_section_chainlink/track_section_chainlink.track_section_chainlink'"));
	ChainMesh = chainMesh.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		hangarMesh(TEXT("'/Game/Meshes/Rail/track_section_hangar/track_section_hangar.track_section_hangar'"));
	HangarMesh = hangarMesh.Object;
}

void ATrackSpline::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	InstancedTrack->SetStaticMesh(TrackMesh);
	InstancedChain->SetStaticMesh(ChainMesh);
	InstancedHangar->SetStaticMesh(HangarMesh);

	//Set Spacing and NumInstances
	FBox TrackBoundingBox = TrackMesh->GetBoundingBox();
	FVector BoxLength = (TrackBoundingBox.Max - TrackBoundingBox.Min);
	Spacing = BoxLength.X + Offset;
	NumInstances = FMath::Floor(Spline->GetSplineLength() / Spacing);

	//Clear previous instances from previous spline transform
	InstancedChain->ClearInstances();
	InstancedTrack->ClearInstances();
	InstancedHangar->ClearInstances();

	//Generate Instances
	for (int i = 0; i <= NumInstances; i++)
	{
		FVector vectorCurrentInstance = GetLocationAtIndex(i);
		FVector vectorNextInstance = GetLocationAtIndex(i + 1);

		FVector vecDistance = vectorNextInstance - vectorCurrentInstance;
		FRotator rotX = UKismetMathLibrary::MakeRotFromX(vecDistance);
		FTransform transformInstance = UKismetMathLibrary::MakeTransform(vectorCurrentInstance, rotX);

		InstancedTrack->AddInstance(transformInstance);
		InstancedChain->AddInstance(transformInstance);
		InstancedHangar->AddInstance(transformInstance);
	}
}

FVector ATrackSpline::GetLocationAtIndex(int32 Index)
{
	return Spline->GetLocationAtDistanceAlongSpline((Spacing * Index), ESplineCoordinateSpace::World);
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

