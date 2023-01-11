// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainController.h"
#include "TrackSpline.h"
#include "Train.generated.h"

UENUM(BlueprintType)
enum class ETrainType : uint8
{
	EMS_Cab UMETA(DisplayName = "Cab"),
	EMS_Locomotive UMETA(DisplayName = "Locomotive"),
	EMS_HPU UMETA(DisplayName = "HPU"),
	EMS_Hoist UMETA(DisplayName = "Hoist")
};

UCLASS()
class ATrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrain();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void SetOnTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintCallable)
	void UpdateBogeyPosition(UPARAM(ref) UStaticMeshComponent* Bogey);

	void UpdateDistance(float DeltaTime);

	void GetTrackSpline();

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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATrainController* TrainController;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Default")
	bool Disabled = false;

protected:

	UPROPERTY(VisibleAnywhere)
	float Distance = 0.f;
};
