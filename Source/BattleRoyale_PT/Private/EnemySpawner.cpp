// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "KawaiiEnemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	GenerateSpawnPoints(70, 25200, 25200, 96);
	Spawn(70);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::Spawn(int32 SpawnLimit)
{
	for (int32 i = 0; i < SpawnLimit; i++)
	{
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // may not want
		GetWorld()->SpawnActor<AKawaiiEnemy>(SpawnTargets[i], Rotation, SpawnInfo);
	}
}

