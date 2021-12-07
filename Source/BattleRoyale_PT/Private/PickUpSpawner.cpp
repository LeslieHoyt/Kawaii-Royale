// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpSpawner.h"
#include "HeartPickUp.h"
#include "StarPickUp.h"

// Sets default values
APickUpSpawner::APickUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickUpSpawner::BeginPlay()
{
	Super::BeginPlay();
	GenerateSpawnPoints(700, 25200, 25200, 100);
	Spawn(700);
}

// Called every frame
void APickUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUpSpawner::Spawn(int32 SpawnLimit)
{
	for (int32 i = 0; i < SpawnLimit; i++)
	{
		int32 pickUpType = FMath::RandRange(0, 1);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // may not want
		switch (pickUpType)
		{
		case 0: 
			GetWorld()->SpawnActor<AHeartPickUp>(SpawnTargets[i], Rotation, SpawnInfo);
			break;
		case 1: 
			GetWorld()->SpawnActor<AStarPickUp>(SpawnTargets[i], Rotation, SpawnInfo);
			break;
		}
	}
}

