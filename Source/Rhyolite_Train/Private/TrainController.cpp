/**

Train controller class implementation mainly used for the spawning, organization, and settings of trains all in one Actor.

Original author: Shea Galley
Current maintainer: Shea Galley

*********************************************************************************/


#include "TrainController.h"
#include "Train.h"

ATrainController::ATrainController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

/**
Spawn child BPs from this class and add to the TrainsInLevel array.
*********************************************************************************/
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
				TrainsInLevel.Insert(spawnedTrain, 0);

				spawnedTrain->SetOnTrack(0);
				spawnedTrain->PreviousTrain = TrainsInLevel[1];

				int numTrainsInLevel = TrainsInLevel.Num();

				for (int32 i = 0; i < numTrainsInLevel; i++)
				{
					//skip over newly spawned train
					if (i > 0)
					{
						auto& train = TrainsInLevel[i];
						auto& prevTrain = TrainsInLevel[i - 1];

						float prevTrainStartPos = prevTrain->StartPosition;
						float distanceFromNextTrain = GetDistanceFromNextTrain(prevTrain);
						float newPosition = distanceFromNextTrain + prevTrainStartPos;

						train->StartPosition = newPosition;
						train->SetOnTrack(newPosition);

						if (i < (numTrainsInLevel - 1)) //prevent attempt to access array element out of bounds
						{
							train->PreviousTrain = TrainsInLevel[i + 1];
						}
						
					}
				}
				
			}
			else //for first train being spawned
			{
				spawnedTrain->TrainController = this;
				spawnedTrain->SetOnTrack(0);
				TrainsInLevel.Add(spawnedTrain);
			}

		}
	}
}


void ATrainController::BeginPlay()
{
	Super::BeginPlay();
}

void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//debugging
	/*for (auto train : TrainsInLevel)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Actor's name is %s"), *train->GetName());
	}*/
}


