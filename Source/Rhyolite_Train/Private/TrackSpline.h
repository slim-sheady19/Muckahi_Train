// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//Set the static meshes of the track
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UInstancedStaticMeshComponent* InstancedTrack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UInstancedStaticMeshComponent* InstancedChain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UInstancedStaticMeshComponent* InstancedHangar;

};
