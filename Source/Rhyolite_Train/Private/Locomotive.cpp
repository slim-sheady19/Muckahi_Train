// Fill out your copyright notice in the Description page of Project Settings.


#include "Locomotive.h"
#include "Kismet/KismetMathLibrary.h"

ALocomotive::ALocomotive()
{
	MiddleBogey = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle Bogey"));
	MiddleBogey->SetupAttachment(RootBogey);
	MiddleBogey->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontBogey = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Bogey"));
	FrontBogey->SetupAttachment(RootBogey);
	FrontBogey->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootBogey);
	Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontConnectionDistanceFromRootBogey = 580.f;
	RearConnectionDistanceFromRootBogey = 80.f;

	//set the bogey distance floats in BP Constructor
}

void ALocomotive::UpdateRotation()
{
	FVector rootBogeyLocation = GetActorLocation();
	FVector frontBogeyLocation = FrontBogey->GetComponentLocation();
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(rootBogeyLocation, frontBogeyLocation);

	Body->SetWorldRotation(lookAtRotation);
}

