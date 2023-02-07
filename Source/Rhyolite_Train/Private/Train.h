// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Train")
	void SetOnTrack(float DistanceFromNextTrain);

	UFUNCTION(CallInEditor, Category = "Train")
	void SetOnTrackEditor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FrontConnectionDistanceFromRootBogey = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RearConnectionDistanceFromRootBogey = 0.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Train")
	ATrain* PreviousTrain;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintCallable)
	void UpdateBogeyPosition(UPARAM(ref) UStaticMeshComponent* Bogey, const float DeltaBogeyDistanceFromRootBogey = 0.f);

	void UpdateDistance(float DeltaTime);

	void GetTrackSpline();

	//virtual void BeginDestroy() override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

	//Bogey that attaches to track spline
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
