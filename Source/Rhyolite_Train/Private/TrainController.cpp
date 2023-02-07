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

			if ((IsValid(spawnedTrain)) && (TrainsInLevel.Num() > 0))
			{
				spawnedTrain->TrainController = this;
				//spawnedTrain->SetOnTrack(0);
				//ATrain* prevTrain = TrainsInLevel.Last();
				//float distanceFromNextTrain = GetDistanceFromNextTrain(spawnedTrain);
				//lastTrain->SetOnTrack(distanceFromNextTrain);
				TrainsInLevel.Insert(spawnedTrain, 0);

				spawnedTrain->SetOnTrack(0);

				//this is crashing editor.  need to figure out how to bump all trains forward when new one is spawned
				int numTrainsInLevel = TrainsInLevel.Num();
				//UE_LOG(LogTemp, Warning, TEXT("The trainsinlevel value is: %d"), numTrainsInLevel);
				for (int32 i = 0; i < numTrainsInLevel; i++)
				{
					//skip over newly spawned train
					if (i > 0)
					{
						auto& train = TrainsInLevel[i];
						auto& prevTrain = TrainsInLevel[i - 1];
						//UE_LOG(LogTemp, Warning, TEXT("The train name is %s"), *train->GetName());
						//UE_LOG(LogTemp, Warning, TEXT("The prevtrain name is %s"), *prevTrain->GetName());

						float prevTrainStartPos = prevTrain->StartPosition;
						float distanceFromNextTrain = GetDistanceFromNextTrain(prevTrain);
						float newPosition = distanceFromNextTrain + prevTrainStartPos;
						UE_LOG(LogTemp, Warning, TEXT("The float value is: %f"), newPosition);

						train->StartPosition = newPosition;
						train->SetOnTrack(newPosition);
					}

					
	
				}
				
			}
			else //for first train being spawned *WORKS*
			{
				spawnedTrain->TrainController = this;
				spawnedTrain->SetOnTrack(0);
				TrainsInLevel.Add(spawnedTrain);
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


