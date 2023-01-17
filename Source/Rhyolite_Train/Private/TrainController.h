// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Train.h"
#include "TrainController.generated.h"


UCLASS()
class ATrainController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor, Category = "Spawning")
	void SpawnTrain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ATrain> TrainBlueprintClass = ATrain::StaticClass();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
