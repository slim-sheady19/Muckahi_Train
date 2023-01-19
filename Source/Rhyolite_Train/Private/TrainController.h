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

	/**This function is being used to clean up the null refs inside the TrainsInLevel array, called from any train that is being deleted.
	* This would be better achieved with using an event binding or delegate.
	* Also would like a way to directly reference the train to destroy in the array rather than looping through the whole array
	 */
	void CleanTrainArray();

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
