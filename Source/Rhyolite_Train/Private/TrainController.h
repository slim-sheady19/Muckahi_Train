/**

Train controller class implementation mainly used for the spawning, organization, and settings of trains all in one Actor.

Original author: Shea Galley
Current maintainer: Shea Galley

*********************************************************************************/

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

	//Spawn child BPs from this class and add to the TrainsInLevel array.
	UFUNCTION(CallInEditor, Category = "Spawning")
	void SpawnTrain();

	//Use this to select which child BP of train to spawn in level from Train Controller
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<ATrain> TrainBlueprintClass = ATrain::StaticClass();

	//Use this to set same train speed on all trains in level with function SetSpeedAllTrains
	UPROPERTY(EditAnywhere, Category = "Organization")
	float TrainSpeed = 200.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Organization")
	TArray<ATrain*> TrainsInLevel;

	UFUNCTION(CallInEditor, Category = "Organization")
		void SetSpeedAllTrains()
	{
		for (auto& train : TrainsInLevel)
		{
			train->Speed = TrainSpeed;
		}
	}

public:	

	virtual void Tick(float DeltaTime) override;

private:

	float GetDistanceFromNextTrain(ATrain* NextTrain)
	{
		return (NextTrain->FrontConnectionDistanceFromRootBogey + NextTrain->RearConnectionDistanceFromRootBogey);
	}

};
