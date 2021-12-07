// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseSpawner.h"

// Sets default values
ABaseSpawner::ABaseSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnTimer = 1.5f;

}

// Called when the game starts or when spawned
void ABaseSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSpawner::Spawn(int32 SpawnLimit)
{
	// Override this function in the child classes
}

void ABaseSpawner::GenerateSpawnPoints(int32 SpawnLimit, int32 XLimit, int32 YLimit, int32 ZLimit)
{
	for (int32 i = 0; i < SpawnLimit; i++)
	{
		int32 RandX = FMath::RandRange(-XLimit, XLimit);
		int32 RandY = FMath::RandRange(-YLimit, YLimit);
		FVector RandLocation(RandX, RandY, ZLimit);
		SpawnTargets.Add(RandLocation);
	}
}