// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Train.h"
#include "Hoist.generated.h"

/**
 * 
 */
UCLASS()
class AHoist : public ATrain
{
	GENERATED_BODY()


protected:

	UFUNCTION(BlueprintCallable)
		void SetBogeyOnSpline(UPARAM(ref)USceneComponent* AttachPoint, UPARAM(ref)UStaticMeshComponent* Bogey);
	
};
