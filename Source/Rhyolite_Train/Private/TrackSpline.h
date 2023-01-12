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

	/**
	This overriden function is called every time the actor's transform is changed, so in this case whenever the spline is moved or 
	lengthened so we can add the or remove the instanced meshes accordingly
	**/
	virtual void OnConstruction(const FTransform& transform) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns a vector in world space at the distance along spline, in terms of units of mesh spacing
	FVector GetLocationAtIndex(int32 Index);

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Customization")
	float Offset = -13.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 NumInstances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USplineComponent* Spline;

protected:


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
