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

	/**This function removes any deleted trains from the array of trains in level
	* This could maybe be improved with a callback/event dispathcer / delegate
	 */
	void RemoveTrainFromArray(ATrain* TrainToRemove)
	{
		TrainsInLevel.Remove(TrainToRemove);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor, Category = "Spawning")
	void SpawnTrain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ATrain> TrainBlueprintClass = ATrain::StaticClass();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Organization")
	TArray<ATrain*> TrainsInLevel;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
