/**

Train parent class that sets default values and contains functions common to all children.

Original author: Shea Galley
Current maintainer: Shea Galley

*********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrackSpline.h"
#include "Train.generated.h"

class ATrainController;

UENUM(BlueprintType)
enum class ETrainType : uint8
{
	EMS_Cab UMETA(DisplayName = "Cab"),
	EMS_Locomotive UMETA(DisplayName = "Locomotive"),
	EMS_HPU UMETA(DisplayName = "HPU"),
	EMS_Hoist UMETA(DisplayName = "Hoist")
};

//maybe create enums in an external file/class?  because I am using the exact ones in the TrainController

UCLASS()
class ATrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrain();

	//Called from TrainController when it has spawned a train
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Train")
	void SetOnTrack(float DistanceFromNextTrain);

	//Same function as above but takes no float so we can call it manually from editor
	UFUNCTION(CallInEditor, Category = "Train")
	void SetOnTrackEditor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FrontConnectionDistanceFromRootBogey = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RearConnectionDistanceFromRootBogey = 0.f;

	//Ref to train ahead (in array) of current train so we can get the correct distance it needs to be from that one
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Train")
	ATrain* PreviousTrain;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	//Called from child BP in tick
	UFUNCTION(BlueprintCallable)
	void UpdateBogeyPosition(UPARAM(ref) UStaticMeshComponent* Bogey, const float DeltaBogeyDistanceFromRootBogey = 0.f);

	//Updating distance float in Tick
	void UpdateDistance(float DeltaTime);

	void GetTrackSpline();

	//Overriding Destroyed() to remove deleted train in editor from TrainsInLevel array
	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	//Every train class has a root bogey that attaches to the track spline
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* RootBogey = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATrackSpline* TrackSpline;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float StartPosition = 0.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ATrainController* TrainController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Default")
	bool Disabled = false;

protected:

	//The distance currently travelled along spline
	UPROPERTY(VisibleAnywhere)
	float Distance = 0.f;
};
