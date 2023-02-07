// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Train.h"
#include "Locomotive.generated.h"

/**
 * 
 */
UCLASS()
class ALocomotive : public ATrain
{
	GENERATED_BODY()

	
public:

	ALocomotive();

	/**
	Create the additional bogeys for this train class and floats for the distance from root bogey
	*********************************************************************************/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MiddleBogey = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float MiddleBogeyDistanceFromRootBogey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* FrontBogey = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FrontBogeyDistanceFromRootBogey;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Body = nullptr;

protected:

	UFUNCTION(BlueprintCallable)
	void UpdateRotation();

	
};
