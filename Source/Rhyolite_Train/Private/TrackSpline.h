// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine\Classes\Components\SplineComponent.h"
#include "TrackSpline.generated.h"

UCLASS()
class ATrackSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrackSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& transform) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetLocationAtIndex(int32 Index);

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customization")
	float Offset = -13.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Customization")
	float SplineLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NumInstances;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;

	//Set the instanced static meshes of the track
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UInstancedStaticMeshComponent* InstancedTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UInstancedStaticMeshComponent* InstancedChain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UInstancedStaticMeshComponent* InstancedHangar;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Meshes")
	UStaticMesh* TrackMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Meshes")
	UStaticMesh* ChainMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Meshes")
	UStaticMesh* HangarMesh;

	float Spacing;

};
