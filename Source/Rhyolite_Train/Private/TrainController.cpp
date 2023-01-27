// Fill out your copyright notice in the Description page of Project Settings.


#include "TrainController.h"
#include "Train.h"

// Sets default values
ATrainController::ATrainController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATrainController::SpawnTrain()
{
	if (IsValid(TrainBlueprintClass))
	{
		UWorld* CurrentLevel = GetWorld();

		if (IsValid(CurrentLevel))
		{
			FTransform spawnTransform = FTransform(); //create transform with default values
			ATrain* spawnedTrain = CurrentLevel->SpawnActor<ATrain>(TrainBlueprintClass, spawnTransform);

			if (spawnedTrain)
			{
				spawnedTrain->TrainController = this;
				spawnedTrain->SetOnTrack();
				TrainsInLevel.Add(spawnedTrain);
				UE_LOG(LogTemp, Warning, TEXT("The train's name is %s"), *spawnedTrain->TrainController->GetName());
				
			}
		}
	}
}


// Called when the game starts or when spawned
void ATrainController::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//debugging
	for (auto train : TrainsInLevel)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *train->GetName());
	}

}


