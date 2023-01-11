// Fill out your copyright notice in the Description page of Project Settings.


#include "Locomotive.h"

ALocomotive::ALocomotive()
{
	MiddleBogey = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Middle Bogey"));
	MiddleBogey->SetupAttachment(RootBogey);
	MiddleBogey->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FrontBogey = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Bogey"));
	FrontBogey->SetupAttachment(RootBogey);
	FrontBogey->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//set the bogey distance floats in BP Constructor
}

