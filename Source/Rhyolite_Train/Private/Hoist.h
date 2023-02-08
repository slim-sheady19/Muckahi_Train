/**

Hoist class (child of ATrain) implementation

Original author: Shea Galley
Current maintainer: Shea Galley

*********************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Train.h"
#include "Hoist.generated.h"


UCLASS()
class AHoist : public ATrain
{
	GENERATED_BODY()

public:

	AHoist();

	/**
	Below are the functions to move the different moving parts of the Hoist with code.
	All functions to be called from child BP in event tick.
	*********************************************************************************/
protected:

	UFUNCTION(BlueprintCallable)
	void SetBogeyOnSpline(UPARAM(ref)USceneComponent* AttachPoint, UPARAM(ref)UStaticMeshComponent* Bogey);

	UFUNCTION(BlueprintCallable)
	void RotateSpreaderBar(UPARAM(ref)UStaticMeshComponent* SpreaderBarToRotate, UPARAM(ref)USceneComponent* AttachPointToLookAt);

	UFUNCTION(BlueprintCallable)
	void RotateAndScaleConnectorTube(
			UPARAM(ref)UStaticMeshComponent* ConnectorTube,
			UPARAM(ref)UStaticMeshComponent* StartConnector,
			UPARAM(ref)UStaticMeshComponent* TargetConnector);
	
};
